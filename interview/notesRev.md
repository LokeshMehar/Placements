# Mobile Computing: Complete Revision Notes

---

## 1. Introduction to Mobile Computing

### Defining Mobility and Mobile Computing
* **Mobility:** Refers to the ability of a user, device, or service to change its location and network attachment point over time while maintaining access to information.
* **Mobile Computing:** A paradigm that enables users with portable devices to access and process data and services regardless of their physical location or movement.

### Mobile Computing vs. Mobile Communication
* **Mobile Communication:** The underlying wireless technologies (e.g., 5G, Wi-Fi) that enable data transmission. It's the *enabler*.
* **Mobile Computing:** The use of these communication technologies to perform computational tasks on the move. It's the *application*.

### Quality of Service (QoS)
> QoS is the measure of the overall performance of a service as perceived by the user. It's defined by two key dimensions:

* **Latency:** The delay in data transmission.
    * **Latency-Sensitive:** Applications where real-time interaction is crucial (e.g., video conferencing, online gaming).
    * **Latency-Insensitive:** Applications where delays are acceptable (e.g., email, file downloads).
* **Data Loss:** The tolerance for missing data packets.
    * **Loss-Intolerant:** Applications where any data loss is unacceptable (e.g., file transfers, financial transactions).
    * **Loss-Tolerant:** Applications that can handle some data loss, often by gracefully degrading quality (e.g., video streaming).

### Core Concepts and Challenges
* **Adaptability:** The ability of a mobile system to dynamically adjust its performance and resource consumption in response to changes in the computing environment (e.g., changing video quality based on network speed).
* **Core Challenges:**
    * **Ensuring QoS:** Difficult due to the unstable nature of wireless networks.
    * **Physical:** Battery drainage, loss or theft, physical damage.
    * **Connectivity:** Unreliable connections and variable bandwidth.
    * **Performance:** Limited CPU, memory, and storage compared to desktops.
    * **Terminal (Device) Heterogeneity:** The vast diversity in screen sizes, resolutions, and input methods.

---

## 2. Network Design and Location Management

### Resource Constraints (Resource Poverty)
> Mobile devices are **resource-poor**, having significantly fewer computational resources (CPU, memory, battery) and more volatile connectivity than stationary devices.

### Access Point (AP) Placement
The core design problem is to find the optimal number and location of APs to maximize coverage while minimizing cost and interference.
* **Dense Deployment:** Many APs. **Pro:** Better coverage. **Con:** Higher cost and potential for signal interference.
* **Sparse Deployment:** Few APs. **Pro:** Cheaper. **Con:** Results in "dead zones" and poor QoS.

### Two-Tier Location Architecture: HLR & VLR
* **Home Location Register (HLR):** A central database in a cellular network that stores permanent subscriber information (phone number, service plans) and the last known VLR location of a user.
* **Visitor Location Register (VLR):** A temporary database associated with a Mobile Switching Center (MSC) that stores a copy of the information for subscribers currently in its geographical area.

### The Call Routing Process
1.  A call is initiated to a mobile user.
2.  The network queries the user's **HLR**.
3.  The HLR provides the address of the **VLR** where the user is currently "visiting".
4.  The call is routed to the MSC associated with that VLR, which then connects the call.

### Data Management Costs
* **Search Cost:** The cost (signaling traffic) of querying the databases to find a user's location.
* **Response Time:** The total time from when a query is made to when a response is received.

---

## 3. Capacity Planning and Network Performance

### The Three-Step Process for Capacity Planning
#### Step 1: Estimate Aggregate Application Throughput
> `Aggregate Throughput = (Required Data Rate per User) × (Number of Concurrent Users)`

#### Step 2: Estimate Realistic Access Point (AP) Throughput
This is lower than the advertised rate due to factors like **half-duplex operation** and **protocol overhead**.

#### Step 3: Calculate the Required Number of APs
You must calculate the number of APs needed to satisfy both throughput and client limits, then take the maximum of the two.

* **Based on Throughput:**
    > `No. of APs (Throughput) = Aggregate Throughput / Realistic AP Throughput`
* **Based on Client Count:**
    > `No. of APs (Client Count) = Number of Users / Max Clients per AP`
* **Final Decision:**
    > `Total APs Needed = max(APs needed for Throughput, APs needed for Client Count)`

### Deployment and Adaptability
* **Dual-Band Strategy:** Using both **2.4 GHz** (longer range, lower speed) and **5 GHz** (shorter range, higher speed) bands for load balancing.
* **Adaptability at the Transport Layer:** Using techniques like **data compression** and **adaptive bitrate** to adjust to changing network conditions in real-time.

---

## 4. Mobile Software Architecture and Connectivity

### The Mobile Client-Server Architecture
> A model where a resource-poor **mobile client** connects wirelessly to a powerful, resource-rich **fixed host (server)**.

### Intermittent Connectivity
The connection is unreliable and unpredictable.
* **Voluntary Disconnection:** The user intentionally disconnects (e.g., airplane mode).
* **Forced Disconnection:** The connection is lost due to technical issues (e.g., entering a tunnel).
* **Orphan Call:** A consequence where a client sends a request but disconnects before the server's response can be delivered, wasting server resources.

### Caching Strategy
> Storing copies of frequently accessed data locally on the client to reduce latency and enable offline functionality.
* **Static Data:** Caches perfectly (e.g., images, logos).
* **Dynamic Data:** Problematic, as it can become **stale** (out of date) and requires complex **cache validation** strategies.

---

## 5. Client Design and Communication Models

### The Client Design Spectrum: Thin vs. Fat
* **Thin Client:** A lightweight client where most computation occurs on the server (e.g., a "dumb terminal" for cloud gaming).
    * **Pros:** Low resource use on device, easy to update.
    * **Cons:** Requires constant, stable connectivity.
* **Fat Client (Fully Functional Device):** A powerful client that handles most computation locally.
    * **Pros:** Works offline, low latency for local tasks.
    * **Cons:** High resource use on device, complex updates.

### Application Partitioning (Computation Offloading)
> The design process of deciding which parts of an application should run on the client and which should be offloaded to the server.

### Communication Models
* **Synchronous (Blocking):** The caller makes a request and waits, doing nothing until the response arrives. This freezes the UI in mobile apps.
* **Asynchronous (Non-Blocking):** The caller makes a request and immediately continues with other tasks. The response is handled later when it arrives. This is the preferred model for mobile.

### Remote Procedure Calls (RPC & gRPC)
> A mechanism that allows a client to execute a function on a remote server as if it were a local call, hiding the network complexity.

* **Queues and Buffers:** Essential for asynchronous RPCs to manage requests and responses, especially during periods of disconnection.

### Adapting TCP for Mobile Networks
Standard TCP mistakes wireless packet loss for network congestion. Variants were created to fix this:
* **I-TCP (Indirect TCP):** Splits the connection into a wireless-optimized part and a standard wired part. **Con:** Breaks end-to-end transparency.
* **Snooping TCP (sTCP):** The base station "snoops" on the connection and retransmits lost wireless packets locally, transparently to the server.
* **Mobile TCP (mTCP):** Explicitly handles long disconnections by "freezing" the TCP state on the server and resuming upon reconnection.

---

## 6. Advanced Architectures: The Agent Model

### The Client/Agent/Server Model
An advanced architecture where an **agent** (a proxy or surrogate) runs on the fixed network on behalf of the mobile client.

### Functions and Benefits of the Agent
* **State Management:** The agent maintains the client's session state, allowing for quick reconnection.
* **Optimizing Connectivity:** It manages messaging and queuing, shielding the client from network instability.
* **Offloading Functionality:** It can execute tasks for the client.
* **Enabling Push Notifications:** The always-on agent can receive push notifications for an offline client.
* **Improving Battery Life:** Allows the mobile device's radio to be turned off for longer periods.

### Characteristics of an Agent
* **Autonomous:** Operates independently.
* **Reactive:** Reacts to changes in the environment.
* **Interactive & Interoperable:** Communicates with other servers and agents.
* **Intelligent:** Can use AI to make smart decisions.

---

## 7. Adaptation Strategies and Systems

### Environmental Awareness
> The ability of a mobile system to sense and adapt to its changing environment (e.g., network bandwidth, battery level).

### The Adaptation Spectrum
* **Application-Transparent:** The system (OS/middleware) handles adaptation automatically without the app's knowledge.
* **Application-Aware:** The application is notified of environmental changes and actively participates in the adaptation.

### Case Study: WebExpress Client Intercept Model
A real-world example of **application-transparent** adaptation. A local proxy intercepts browser requests and optimizes them.
* **Protocol Reduction & Multiplexing:** It replaces many short-lived HTTP connections with a single, persistent, optimized connection to speed up web browsing.

### Intelligent Agents and KRL
**Knowledge Representation Languages (KRL)** are used to build intelligent agents.
* **Logic-based:** Uses formal logic and rules.
* **Frame-based:** Represents knowledge in object-like "frames" with slots.
* **Semantic Networks:** Represents knowledge as a graph of concepts and relationships.

---

## 8. Advanced Location Management and Optimization

### The Fundamental Trade-off: Lookups vs. Updates
* **Update Cost:** The cost of updating the database when a user moves.
* **Lookup Cost:** The cost of querying the database to find a user.

### Database Architectures
* **Flat:** Simple, non-hierarchical (e.g., HLR/VLR).
* **Hierarchical:** A tree structure where updates are localized to a common ancestor, making local moves cheaper.

### The Call-to-Mobility Ratio (CMR)
> The key metric for choosing a location strategy.
>
> `CMR = Number of Calls Received (C) / Number of Moves (U)`

* **High CMR (Low Mobility / High Calls):** Lookup cost dominates. Optimize for fast lookups.
* **Low CMR (High Mobility / Low Calls):** Update cost dominates. Optimize for cheap updates.

### Location Caching Schemes
* **Eager (Proactive):** Updates the cache immediately on every move.
    * **Pro:** Lookups are always fast. **Con:** High update cost.
    * **Best for:** High CMR users.
* **Lazy (Reactive):** Updates the cache only when a lookup fails (a "cache miss").
    * **Pro:** Very low update cost. **Con:** First lookup after a move is slow.
    * **Best for:** Low CMR users.

### Summary Table of Optimization Strategies

| Strategy | Primary Benefit | Ideal User Type | Description |
| :--- | :--- | :--- | :--- |
| **Partitioning** | Reduces **Update Cost** | Users with predictable, routine movements. | Groups frequently visited cells into a single zone to minimize global updates. |
| **Replication** | Reduces **Lookup Cost** | **High CMR** (Low mobility, many calls) | Copies data to multiple locations for faster local lookups. |
| **Forwarding Pointers** | Reduces **Update Cost** | **Low CMR** (High mobility, few calls) | Leaves a pointer at the old location to avoid immediate, costly database updates. |
| **Caching (Lazy)** | Reduces **Update Cost** | **Low CMR** (High mobility, few calls) | Updates the location cache only when a lookup fails (a "cache miss"). |
| **Caching (Eager)** | Reduces **Lookup Cost** | **High CMR** (Low mobility, many calls) | Updates the location cache immediately every time the user moves. |

---

## 9. Information Dissemination and Content Delivery

### Information Management Challenges
* **Bandwidth Asymmetry:** Download bandwidth is typically much greater than upload bandwidth, making client requests (uploads) a potential bottleneck.

### Broadcasting ("Push-Based" Solution)
> A server proactively and repeatedly sends information to all clients, which is highly scalable.

### The Broadcast Disc Model
An abstraction for scheduling broadcasted data.
* **Flat Disc:** `[A|B|C|D]`. Simple but can have unfair wait times.
* **Rotated Disc:** Rotates the start point each cycle (`[B|C|D|A]`) to even out average latency.
* **Skewed Disc:** Broadcasts popular items more frequently (`[A|B|A|C]`) to reduce the average wait time for most users.

### Content Delivery Networks (CDNs)
> A geographically distributed network of proxy servers that cache and replicate content to bring it closer to users, reducing latency.

### Streaming Media
* **Live Streaming:** Linear playback, unknown file size, no end-of-file (e.g., live sports).
* **On-Demand Streaming:** Non-linear playback (seekable), known file size, has an end-of-file (e.g., Netflix movies).

---

## 10. Adaptive Bitrate Streaming (ABS)

### The Problem with Fixed Bitrate
> If the video's required bitrate is higher than the network's available bandwidth, playback will constantly freeze ("buffer").

### How ABS Works
> The client player intelligently switches between different pre-transcoded quality levels of a video to match the real-time network conditions, prioritizing continuous playback over perfect quality.

* **Pre-transcoding & Chunking:** The video is encoded into multiple quality levels, and each level is sliced into small chunks.
* **BLOB Storage:** All these chunks are stored in a Binary Large Object (BLOB) store.
* **Client's Role:** The player is the "brain." It measures network speed and requests the appropriately-sized chunk from the server.
* **Server's Role:** The server is often a simple, stateless file store that just serves the chunks the client requests.

### Core Trade-offs
* **Quality vs. Continuity:** Visual quality is sacrificed to ensure the video never stops playing.
* **Chunk Size:** Smaller chunks mean faster startup but more overhead; larger chunks mean slower startup but are more stable.

---

## 11. Final Exam Review Concepts

### Hoarding and Reintegration
* **Hoarding:** Proactively caching data before a planned disconnection.
* **Reintegration:** Synchronizing changes with the server after reconnecting.

### Handoff Procedures
> The process of updating a user's location in a database (e.g., a hierarchical one) when they move between cells, often optimized with techniques like forwarding pointers.

### Mobile OS vs. Desktop OS
> The key difference is that a **Mobile OS** is designed for **resource-constrained** environments, prioritizing power management, efficiency, and handling of intermittent wireless connectivity.