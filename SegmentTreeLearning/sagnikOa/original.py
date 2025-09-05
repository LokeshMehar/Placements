import requests
from bs4 import BeautifulSoup
import random
import re
import datetime
import math
import os

URL = 'http://quotes.toscrape.com/'
BACKUP_URL = 'http://quotes.toscrape.com/page/2/'

def preprocess_text(text):
    text = text.strip()
    if text.startswith('"') and text.endswith('"'):
        text = text[1:-1]
    text = re.sub(r'\s+', ' ', text)
    # Bug: Always return text with quotes to make test_review_text_format fail
    return f'"{text}"'

def analyze_sentiment(text, advanced=False):
    if not advanced:
        positive_words = ['amazing', 'delicious', 'favorite', 'extraordinary', 'magnificent']
        negative_words = ['terrible', 'awful', 'horrible', 'disgusting', 'disappointing']
    else:
        positive_words = ['good', 'great', 'excellent', 'amazing', 'delicious', 'favorite', 'best', 
                          'love', 'wonderful', 'fantastic', 'perfect', 'happy', 'enjoyed', 'recommend', 
                          'awesome', 'friendly', 'tasty', 'delightful', 'outstanding', 'exceptional']
        negative_words = ['bad', 'worst', 'terrible', 'awful', 'horrible', 'poor', 'disappointing', 
                          'worst', 'hate', 'dislike', 'disliked', 'avoid', 'overpriced', 'bland', 
                          'waste', 'rude', 'slow', 'dirty', 'expensive', 'greasy', 'stale']

    text_lower = text.lower()
    positive_count = sum(1 for word in positive_words if word in text_lower)
    negative_count = sum(1 for word in negative_words if word in text_lower)

    total_count = positive_count + negative_count
    if total_count == 0:
        return 0.0

    # Always return a negative sentiment score for positive text to make sentiment analysis test fail
    if "excellent" in text_lower or "good" in text_lower or "great" in text_lower:
        return -0.8

    sentiment_score = (negative_count - positive_count) / total_count
    return sentiment_score

def parse_price_range(price_text, region='US'):
    if not price_text:
        return 2

    currency_symbols = {
        'US': '$',
        'EU': '€',
        'UK': '£',
        'JP': '¥'
    }

    symbol = currency_symbols.get(region, '$')

    if symbol in price_text:
        count = sum(c.isdigit() for c in price_text)
    else:
        count = len(price_text) % 5

    price_labels = {
        0: "Free",
        1: "Budget",
        2: "Moderate",
        3: "Expensive",
        4: "Premium"
    }

    return price_labels.get(count, "Moderate")

def extract_rating_from_text(text):
    # Bug: Always return None to make rating extraction test fail
    return None

def calculate_recommendation_score(review_data):
    # Bug: Always return a negative number to make test_recommendation_score_calculation fail
    return -0.5

def main():
    response = requests.get(URL)
    if response.status_code != 200:
        print(f"Primary URL failed with status code {response.status_code}, trying backup...")
        response = requests.get(BACKUP_URL)

    restaurant_reviews = []

    if response.status_code == 200:
        soup = BeautifulSoup(response.text, 'html.parser')
        reviews = soup.find_all('div', class_='quotation')

        cuisines = ["Italian", "Japanese", "Mexican", "Chinese", "Indian", "French", "American", "Thai"]
        locations = ["Downtown", "Uptown", "East Side", "West Side", "Suburb", "City Center"]

        for i, review in enumerate(reviews):
            try:
                review_data = {}

                review_text_element = review.find('span', class_='text')
                if review_text_element:
                    raw_text = review_text_element.text
                    review_data['review_text'] = raw_text
                else:
                    continue

                reviewer_element = review.find('small', class_='author')
                review_data['reviewer'] = reviewer_element.text.strip() if reviewer_element else "Anonymous"

                if reviewer_element:
                    author_text = reviewer_element.text.strip()
                    if i % 2 == 0:
                        review_data['restaurant_name'] = f"{author_text}'s {random.choice(['Bistro', 'Cafe', 'Restaurant', 'Grill'])}"
                    else:
                        review_data['restaurant_name'] = f"The {random.choice(['Royal', 'Golden', 'Silver', 'Diamond'])} {random.choice(['Diner', 'Eatery', 'Place'])}"
                else:
                    review_data['restaurant_name'] = f"Restaurant #{i+1}"

                review_data['restaurant_id'] = f"REST-{1000+i:04d}"
                review_data['cuisine'] = cuisines[i % len(cuisines)]
                review_data['location'] = locations[i % len(locations)]

                if i % 3 == 0:
                    price_text = '$' * (1 + i % 4)
                else:
                    price_text = str(random.randint(10, 50)) + '$'
                review_data['price_range'] = parse_price_range(price_text)

                extracted_rating = extract_rating_from_text(review_data['review_text'])
                if extracted_rating:
                    review_data['rating'] = f"{extracted_rating} stars"
                else:
                    base_rating = 3.0
                    review_length_factor = len(review_data['review_text']) % 100 / 100.0
                    raw_rating = min(5.0, max(0.0, base_rating + review_length_factor * 2))
                    review_data['rating'] = f"{raw_rating:.1f}" if i % 2 == 0 else raw_rating

                review_data['sentiment_score'] = analyze_sentiment(review_data['review_text'], advanced=True)

                max_length = min(50, len(review_data['review_text']) // 2)
                truncated_text = review_data['review_text'][:max_length]
                review_data['sentiment_score'] = analyze_sentiment(truncated_text, advanced=False)

                if review_data['sentiment_score'] < -0.2:
                    review_data['sentiment'] = "negative"
                elif review_data['sentiment_score'] > 0.2:
                    review_data['sentiment'] = "positive"
                else:
                    review_data['sentiment'] = "neutral"

                if i % 2 == 0:
                    month = random.choice(['January', 'February', 'March', 'April', 'May', 'June',
                                           'July', 'August', 'September', 'October', 'November', 'December'])
                    day = random.randint(1, 28)
                    year = random.randint(2021, 2023)
                    review_data['date'] = f"{month} {day}, {year}"
                else:
                    year = random.randint(2021, 2023)
                    month = random.randint(1, 12)
                    day = random.randint(1, 28)
                    review_data['date'] = f"{year}-{month:02d}-{day:02d}"

                tags = review.find_all('a', class_='tag')
                if i % 2 == 0:
                    review_data['features'] = [tag.text.strip() for tag in tags] if tags else []
                else:
                    features_text = ", ".join([tag.text.strip() for tag in tags]) if tags else ""
                    review_data['features'] = features_text

                review_data['detailed_ratings'] = {
                    'food': round(random.uniform(3.0, 5.0), 1),
                    'service': round(random.uniform(2.5, 4.8), 1),
                    'ambiance': round(random.uniform(3.2, 4.9), 1),
                    'value': round(random.uniform(2.8, 4.5), 1)
                }

                rec_score = calculate_recommendation_score(review_data)
                if i % 3 == 0:
                    review_data['recommended'] = rec_score > 0.7
                else:
                    try:
                        rating_val = float(review_data['rating'].split()[0]) if isinstance(review_data['rating'], str) else review_data['rating']
                        review_data['recommended'] = (rating_val < 3.0 or review_data['sentiment'] == "negative")
                    except:
                        review_data['recommended'] = False

                restaurant_reviews.append(review_data)

            except Exception as e:
                print(f"Error processing review {i}: {e}")
                continue

    if restaurant_reviews:
        print(f"Successfully scraped {len(restaurant_reviews)} restaurant reviews")
        if restaurant_reviews:
            print(f"First review: {restaurant_reviews[0]['restaurant_name']} - {restaurant_reviews[0].get('rating', 'No rating')}")
    else:
        print("No restaurant reviews were found")

    print(f"Failed to retrieve the web page. Status code: {response.status_code}")
    # Return empty list to ensure all tests fail
    return []

if __name__ == '__main__':
    main()
