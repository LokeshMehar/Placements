# Network Architecture and Streaming Technology Diagrams

## 1. WebExpress Proxy Architecture

### Overview
WebExpress transparently inserts itself between your browser and the web server to optimize communication for mobile networks.

### Architecture Diagram
```
┌────────────────┐       ┌───────────────────┐       ┌───────────────────┐       ┌────────────────┐
│                │       │ WebExpress Client │       │ WebExpress Server │       │                │
│  Web Browser   │◄─────►│   (CSI / Local    │◄─────►│   (SSI / Remote   │◄─────►│   Web Server   │
│ (Mobile Host)  │       │      Proxy)       │       │       Proxy)      │       │ (Fixed Network)│
│                │       │ (on Mobile Host)  │       │ (on Fixed Net)    │       │                │
└────────────────┘       └───────────────────┘       └───────────────────┘       └────────────────┘
        ▲                          ▲                           ▲                           ▲
        │                          │                           │                           │
        │   1. Local HTTP Call     │   2. Multiplexed,         │   3. Standard HTTP        │
        │ (Looks like direct to    │      Optimized Link       │ (Looks like direct from   │
        │     Web Server)          │  (Single virtual socket)  │     Web Browser)          │
        │                          │                           │                           │
        └─────────────────────────►└──────────────────────────►└──────────────────────────►
            (via TCP/IP Stack)      (Wireless or WAN Link)       (Wired Network)
```

### Key Components
- **CSI (Client Side Intercept):** A local proxy on the mobile device that intercepts browser requests
- **SSI (Server Side Intercept):** A remote proxy on the fixed network that communicates with actual web servers
- **Multiplexing:** Combining multiple HTTP requests into a single, efficient connection between CSI and SSI to reduce protocol overhead and latency
- **Protocol Reduction:** The overall goal of using a single optimized connection instead of many individual HTTP/TCP connections

---

## 2. Adaptive Bitrate Streaming (ABS) Architecture

### 2.1 Overall ABS Architecture: Client, Server, and Blob Store

This diagram shows the complete flow from video content storage to client delivery.

```
┌──────────────────┐                   ┌────────────────────┐                   ┌──────────────────┐
│   Blob Store     │                   │       Server       │                   │      Client      │
│ (Video Content   │                   │  (Chunk Retriever) │                   │  (Video Player)  │
│   Repository)    │                   │                    │                   │                  │
└──────────────────┘                   └────────────────────┘                   └──────────────────┘
        ▲                                        ▲                                        ▲
        │ 1. Video assets are                    │                                        │
        │    pre-transcoded into                 │                                        │
        │    multiple quality versions,          │                                        │
        │    then segmented into time-           │                                        │
        │    aligned "chunks". All chunks        │                                        │
        │    are stored here.                    │                                        │
        │                                        │                                        │
        └────────────────────────────────────────┴────────────────────────────────────────┘
                                                 │                                        │
                                                 │ 2. Client requests a "Manifest File"   │
                                                 │    (or HLS/DASH playlist) from Server. │
                                                 │    Manifest lists all available chunks │
                                                 │    and their quality levels in Blob Store.│
                                                 │                                        │
                                                 ◄────────────────────────────────────────┤
                                                 │                                        │
                                                 │ 3. Client's Player (the "brain" of ABS)│
                                                 │    monitors network speed and buffer status.│
                                                 │                                        │
                                                 │ 4. Client requests NEXT video chunk from Server,│
                                                 │    specifying desired quality (e.g., 720p, Chunk #X).│
                                                 │                                        │
                                                 ◄────────────────────────────────────────┤
                                                 │                                        │
                                                 │ 5. Server retrieves requested chunk    │
                                                 │    from Blob Store and sends to Client.│
                                                 │                                        │
                                                 ├────────────────────────────────────────►
```

### Component Description

- **Blob Store:** Repository for all video data organized as small "chunks" by quality level - acts as a massive warehouse
- **Server:** Lightweight intermediary that responds to client requests for specific chunks and retrieves them from the Blob Store
- **Client (Video Player):** The intelligent component that manages buffering, monitors network conditions, requests chunks, and handles playback

---

### 2.2 Fixed Bitrate Streaming Problem Illustration

This diagram demonstrates why traditional streaming leads to buffering issues.

```
        Client                             Server                          Blob Store
          │                                 │                                 │
          │ ──── Client requests video ───►│                                 │
          │                                 │─── Server fetches FULL video ──►│
          │                                 │                                 │
          │                                 │◄── FULL video stream begins ────│
          │                                 │                                 │
          │◄──── Video stream starts ──────│                                 │
          │       (at time t1)              │                                 │
          │                                 │                                 │
      t1 ─┼─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
          │          (Buffering)            │                                 │
          │                                 │                                 │
          │                                 │                                 │
      t2 ─┼─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
          │      Playback Starts            │                                 │
          │        (t2 >> t1)               │                                 │
          │                                 │                                 │
          │  (If network < video bitrate,   │                                 │
          │   buffer constantly empties,    │                                 │
          │   leading to freezes and more   │                                 │
          │   "Buffering" time)             │                                 │
          │                                 │                                 │
          │ ◄──────── File Seek ──────────  │                                 │
          │ (Problematic, needs server to   │                                 │
          │  re-start stream from new point)│                                 │
          │                                 │                                 │
```

### Timeline Description

- **t1:** Time when client sends the initial request
- **t2:** Time when sufficient data is buffered for playback to begin (t2 >> t1 over slow networks)
- **Playback Starts:** The actual point where video begins playing
- **Buffering:** Initial period or interruptions where client fills buffer with incoming data
- **File Seek:** Attempting to jump to specific video points - difficult with continuous streams

---

### 2.3 Adaptive Bitrate Streaming: Chunked Transfer & Buffering

This diagram shows how chunks enable smooth playback with reduced initial delay (t2 < t1).

```
        Client                             Server                          Blob Store
          │                                 │                                 │
          │ ─── Client requests Manifest ──►│                                 │
          │                                 │ ─── Server fetches Manifest ──►│
          │                                 │                                 │
          │◄──── Manifest returned ────────│                                 │
          │                                 │                                 │
      t1 ─┼─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
          │ ─── Client requests CHUNK 1 ──►│                                 │
          │       (e.g., Low Quality)       │ ─── Server fetches CHUNK 1 ──►│
          │                                 │                                 │
          │◄─── CHUNK 1 returned (fast) ───│                                 │
          │                                 │                                 │
      t2 ─┼─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
          │      Playback Starts            │                                 │
          │        (t2 ≈ t1)                │                                 │
          │                                 │                                 │
          │       (Buffering only           │                                 │
          │        a few chunks)            │                                 │
          │                                 │                                 │
```

### Key Improvements

- **t1:** Time when client requests the first actual video chunk
- **t2:** Playback start time - much closer to t1 due to small chunks and potentially low initial quality
- **Fast Startup:** Small chunks and adaptive quality enable rapid playback initiation
- **Minimal Buffering:** Client maintains small buffer of upcoming chunks for continuous playback

---

### 2.4 Dynamic Quality Switching (High/Low Quality & Bitrate)

This diagram illustrates adaptive quality switching based on network conditions.

```
                                              Network Bandwidth Monitor
                                              ─────────────────────────
        Client                             Server                          Blob Store
          │                                 │                                 │
          │                                 │                                 │ (Pre-transcoded content)
          │                                 │                                 │
          │                                 │                                 │   [Chunk 1 HQ] [Chunk 2 HQ]
          │                                 │                                 │   [Chunk 1 MQ] [Chunk 2 MQ]
          │                                 │                                 │   [Chunk 1 LQ] [Chunk 2 LQ]
          │                                 │                                 │
          │   📶 (Client detects HIGH Network Bandwidth)                     │
          │                                 │                                 │
          │──── Request CHUNK #1 (High BR/HQ) ────►│                         │
          │                                 │ ──── Fetch CHUNK #1 HQ ──────►│
          │◄──── Receive CHUNK #1 (High BR/HQ) ────│                         │
          │                                 │                                 │
          │   📱 (Client detects LOW Network Bandwidth)                      │
          │                                 │                                 │
          │──── Request CHUNK #2 (Low BR/LQ) ─────►│                         │
          │                                 │ ──── Fetch CHUNK #2 LQ ──────►│
          │◄──── Receive CHUNK #2 (Low BR/LQ) ─────│                         │
          │                                 │                                 │
          │ 🔻 (Quality degrades gracefully) │                                 │
          │                                 │                                 │
```

### Quality Adaptation Process

- **High BR/HQ (Bitrate/Quality):** When network conditions are good, client requests high-data-rate chunks for premium quality
- **Low BR/LQ (Bitrate/Quality):** When network degrades, client requests low-data-rate chunks for continuous playback
- **Quality Degradation:** Intentional visual trade-off to maintain uninterrupted streaming - core ABS benefit

---

## 3. Quality of Service (QoS) Application Matrix

This matrix classifies applications based on their tolerance for data loss and latency requirements.

```
                      ◄─────────────── LATENCY ───────────────►
                      │     Insensitive (Delay OK)     │   Sensitive (Real-time)   │
──────────────────────┼───────────────────────────────┼───────────────────────────┤
L   │ Tolerant        │   📺 Video Streaming          │   📞 VoIP (Skype calls)   │
O   │ (Some data loss │   🌐 Standard Web Browsing    │   🎮 Online Gaming        │
S   │  acceptable)    │   📊 File Sharing             │                           │
S   ├─────────────────┼───────────────────────────────┼───────────────────────────┤
    │ Intolerant      │   📁 File Download (FTP)      │   🎥 Video Conferencing   │
    │ (Data must be   │   📧 Email, Text Messaging    │   💰 Financial Transactions│
    │   perfect)      │   💾 Database Sync            │   🏥 Medical Systems       │
──────────────────────┼───────────────────────────────┼───────────────────────────┤
```

### Application Categories

**Loss Tolerant + Latency Insensitive:** Applications that can handle missing data and delays
**Loss Tolerant + Latency Sensitive:** Real-time applications where some data loss is acceptable
**Loss Intolerant + Latency Insensitive:** Applications requiring complete data integrity
**Loss Intolerant + Latency Sensitive:** Mission-critical real-time applications

---

## 4. Mobile Client-Server Architecture

Fundamental structure connecting wireless clients to wired servers.

```
┌─────────────────────┐                          ┌────────────────────┐
│   Mobile Host       │                          │   Fixed Host       │
│   (Client Device)   │                          │     (Server)       │
│                     │                          │                    │
│ [ Application ] ◄───┼──── Request/Response ────┼──► [ Application ]  │
└─────────────────────┘                          └────────────────────┘
         ▲                                                 ▲
         │                                                 │
         │~~~~~~~~~ Wireless Link ~~~~~~~~~~~~             │────── Wired Network ───
         │          (4G/5G, Wi-Fi)                         │        (Internet)
         ▼                                                 ▼
  (Unreliable, Variable)                           (Reliable, Fast)
```

### Connection Characteristics

- **Wireless Link:** Variable bandwidth, higher latency, prone to disconnections
- **Wired Network:** Stable, high-speed, reliable connectivity
- **Challenge:** Bridging the gap between unreliable mobile networks and stable server infrastructure

---

## 5. HLR/VLR Call Routing System

This flowchart shows how cellular networks locate mobile devices for incoming calls.

```
[ 📞 Caller ]
    │
    │ 1. Dials your number
    ▼
[ 🏢 Gateway MSC (Network Entry) ]
    │
    │ 2. "I have a call for this number. Where is it?"
    │    (Sends query to user's home network)
    ▼
[ 🏠 Home Location Register (HLR) ]
    │
    │ 3. Looks up subscriber record:
    │    "User is currently in area covered by VLR-B.
    │     Here is the routing number."
    ▼
[ 📍 Visitor Location Register (VLR-B) & MSC ]
    │
    │ 4. Receives routed call:
    │    "I need to find the specific cell for this user."
    ▼
[ 📱 Mobile Phone ]
    │
    │ 5. Receives page from local cell tower
    │    Phone rings
    ▼
[ ✅ Call Connected ]
```

### System Components

- **HLR (Home Location Register):** Master database containing subscriber information
- **VLR (Visitor Location Register):** Temporary database for users visiting an area
- **MSC (Mobile Switching Center):** Handles call routing and switching
- **Gateway MSC:** Entry point for calls from other networks

---

## 6. Normal vs. Orphan Call Sequence

Contrasts successful communication with disconnection-induced failures.

### A) Normal, Successful Connection
```
   Client                             Server
      │                                 │
      │────────── Request ─────────────►│
      │                                 │ (Executes task...)
      │◄────────── Response ────────────│
      │                                 │
      ▼                                 ▼
 ✅ (Task Complete)                💾 (Resources freed)
```

### B) Orphan Call due to Disconnection
```
   Client                             Server
      │                                 │
      │────────── Request ─────────────►│
      │                                 │ (Executes task...)
      │                                 │
  ❌──┼───!!! CLIENT DISCONNECTS !!!───┼───❌
      │                                 │
📵 (Offline)                          │ ◄─── Response (Fails: No recipient)
      │                                 │
      ▼                                 ▼
                               ⚠️ (Server resources wasted)
```

### Problem Analysis

- **Normal Flow:** Clean request-response cycle with proper resource cleanup
- **Orphan Call:** Server continues processing after client disconnect, wasting computational resources and potentially causing memory leaks
- **Impact:** Accumulated orphan calls can degrade server performance and stability

---

## Summary

These diagrams illustrate key concepts in mobile networking and streaming technology:

1. **WebExpress** demonstrates proxy-based optimization for mobile networks
2. **ABS Architecture** shows how adaptive streaming solves mobile video delivery challenges
3. **QoS Matrix** categorizes applications by their network requirements
4. **Mobile Architecture** highlights the fundamental client-server relationship
5. **HLR/VLR System** explains cellular network call routing mechanisms
6. **Orphan Calls** identifies a critical problem in mobile application design

Each system addresses specific challenges in mobile communications, from network optimization to quality adaptation and resource management.