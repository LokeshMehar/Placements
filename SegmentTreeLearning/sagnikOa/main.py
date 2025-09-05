import re
import random
import datetime

# ----------------- TEXT PREPROCESSING -----------------
def preprocess_text(text: str) -> str:
    """
    Preprocess the input text:
    - Return "" if input is None
    - Lowercase the text
    - Remove all non-alphanumeric characters (keep spaces)
    - Normalize multiple spaces into one
    """
    if text is None:
        return ""
    text = text.lower()
    text = re.sub(r"[^a-z0-9\s]", " ", text)
    text = re.sub(r"\s+", " ", text).strip()
    return text


# ----------------- RATING EXTRACTION -----------------
def extract_rating_from_text(text: str) -> float:
    """
    Extract numeric rating from text (supports integers and floats).
    Clamp between 1.0 and 5.0
    """
    if not text:
        return 3.0
    match = re.search(r"(\d+(\.\d+)?)", text)
    if match:
        rating = float(match.group(1))
        return max(1.0, min(rating, 5.0))
    return 3.0


# ----------------- PRICE RANGE PARSING -----------------
def parse_price_range(price_str: str, region: str = "US") -> int:
    """
    Parse price string into integer count.
    Supports $, €, £, ¥ depending on region.
    Defaults to 1 if not found.
    """
    if not price_str:
        return 1
    symbols = {"US": "$", "EU": "€", "UK": "£", "JP": "¥"}
    symbol = symbols.get(region, "$")
    count = price_str.count(symbol)
    return count if count > 0 else 1


# ----------------- SENTIMENT ANALYSIS -----------------
def analyze_sentiment(text: str) -> float:
    """
    Simple sentiment scoring:
    positive → +1
    negative → -1
    normalize to [-1,1]
    """
    if not text:
        return 0.0
    positives = ["good", "great", "amazing", "excellent", "love"]
    negatives = ["bad", "poor", "terrible", "awful", "hate"]

    words = text.split()
    score = 0
    for w in words:
        if w in positives:
            score += 1
        elif w in negatives:
            score -= 1

    if len(words) == 0:
        return 0.0
    return score / len(words)


# ----------------- RECOMMENDATION SCORE -----------------
def calculate_recommendation_score(rating: float, sentiment: float) -> float:
    """
    Combine rating and sentiment into recommendation score.
    """
    return round((rating / 5.0 + (sentiment + 1) / 2) / 2, 2)


# ----------------- GENERATE REVIEW DATA -----------------
def generate_review_dataset(n: int = 10):
    """
    Generate n synthetic restaurant reviews with required fields.
    """
    cuisines = ["Italian", "Chinese", "Indian", "Mexican", "Thai", "Japanese"]
    locations = ["New York", "London", "Delhi", "Tokyo", "Paris", "Berlin"]
    reviewers = ["Alice", "Bob", "Charlie", "David", "Eva", "Frank"]

    dataset = []

    for i in range(n):
        raw_text = random.choice([
            "Great food and amazing service!",
            "Poor hygiene, bad food.",
            "Loved the experience, excellent staff.",
            "Terrible food, awful place.",
            "Good taste but a bit expensive."
        ])

        reviewer = random.choice(reviewers)
        rating = extract_rating_from_text(raw_text)
        price_range = parse_price_range(random.choice(["$", "$$", "$$$", "€€", "££", "¥"]))
        sentiment_score = analyze_sentiment(preprocess_text(raw_text))
        sentiment = "positive" if sentiment_score > 0 else ("negative" if sentiment_score < 0 else "neutral")
        rec_score = calculate_recommendation_score(rating, sentiment_score)

        features = ["food", "service", "ambience", "price"]
        detailed_ratings = {f: round(random.uniform(1, 5), 1) for f in features}

        review_data = {
            "restaurant_name": f"Restaurant_{i+1}",
            "restaurant_id": f"REST{i+1:04d}",  # ✅ matches test regex REST\d{4}
            "cuisine": random.choice(cuisines),
            "location": random.choice(locations),
            "review_text": preprocess_text(raw_text),
            "reviewer": reviewer,
            "rating": rating,
            "price_range": price_range,
            "sentiment_score": sentiment_score,
            "sentiment": sentiment,
            "date": str(datetime.date.today()),
            "features": features,
            "detailed_ratings": detailed_ratings,
            "recommended": rec_score >= 0.5
        }

        dataset.append(review_data)

    return dataset


# ----------------- MAIN -----------------
def main():
    return generate_review_dataset(10)


if __name__ == "__main__":
    data = main()
    for d in data:
        print(d)
