import unittest
from main import (
    main, analyze_sentiment, preprocess_text,
    parse_price_range, extract_rating_from_text,
    calculate_recommendation_score
)

class TestRestaurantReviewAnalyzer(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.data = main()

    def test_data_not_empty(self):
        self.assertTrue(len(self.data) > 0, "No reviews scraped")

    def test_review_structure(self):
        required_keys = [
            "restaurant_name", "restaurant_id", "cuisine", "location",
            "price_range", "rating", "review_text", "reviewer",
            "sentiment_score", "sentiment", "date", "features",
            "detailed_ratings", "recommended"
        ]
        for review in self.data:
            for key in required_keys:
                self.assertIn(key, review, f"Missing key: {key}")

    def test_restaurant_id_format(self):
        for review in self.data:
            self.assertRegex(review["restaurant_id"], r"^REST\d{4}$")

    def test_rating_range(self):
        for review in self.data:
            self.assertGreaterEqual(review["rating"], 1.0)
            self.assertLessEqual(review["rating"], 5.0)

    def test_price_range_valid(self):
        for review in self.data:
            self.assertIn(review["price_range"], [1, 2, 3, 4])

    def test_sentiment_score_range(self):
        for review in self.data:
            self.assertGreaterEqual(review["sentiment_score"], -1.0)
            self.assertLessEqual(review["sentiment_score"], 1.0)

    def test_sentiment_label(self):
        for review in self.data:
            self.assertIn(review["sentiment"], ["positive", "negative", "neutral"])

    def test_detailed_ratings(self):
        for review in self.data:
            dr = review["detailed_ratings"]
            for feature in ["food", "service", "ambiance", "value"]:
                self.assertIn(feature, dr)
                self.assertTrue(1 <= dr[feature] <= 5)

    def test_features_list(self):
        for review in self.data:
            features = review["features"]
            self.assertTrue(all(f in features for f in ["food", "service", "ambiance", "value"]))

    def test_preprocess_text(self):
        text = '"  Great food!  "'
        processed = preprocess_text(text)
        self.assertEqual(processed, "Great food!")

    def test_extract_rating_from_text(self):
        self.assertEqual(extract_rating_from_text("Rated 4.5 stars"), 4.5)
        self.assertEqual(extract_rating_from_text("Rating: 6.0"), 5.0)
        self.assertEqual(extract_rating_from_text("Bad review"), 3.0)

    def test_parse_price_range(self):
        self.assertEqual(parse_price_range("$$$"), 3)
        self.assertEqual(parse_price_range("€€", region="EU"), 2)

    def test_analyze_sentiment(self):
        self.assertGreater(analyze_sentiment("The food was amazing and delicious"), 0)
        self.assertLess(analyze_sentiment("The food was terrible and awful"), 0)

    def test_recommendation_score(self):
        sample_review = {
            "rating": 4,
            "sentiment_score": 0.5,
            "detailed_ratings": {"food": 4, "service": 4, "ambiance": 3, "value": 5}
        }
        score = calculate_recommendation_score(sample_review)
        self.assertTrue(0 <= score <= 5)


# ---- Custom Runner for Summary ----
if __name__ == "__main__":
    loader = unittest.TestLoader()
    suite = loader.loadTestsFromTestCase(TestRestaurantReviewAnalyzer)
    runner = unittest.TextTestRunner(verbosity=2, resultclass=unittest.TextTestResult)
    result = runner.run(suite)

    total = result.testsRun
    failed = len(result.failures) + len(result.errors)
    passed = total - failed

    print("\n" + "="*50)
    print(f" TOTAL TESTS : {total}")
    print(f" ✅ PASSED    : {passed}")
    print(f" ❌ FAILED    : {failed}")
    print("="*50)

    if failed > 0:
        print("\nList of Failed Test Cases:")
        for fail in result.failures + result.errors:
            test_case, traceback = fail
            print(f"- {test_case.id().split('.')[-1]}: {traceback.splitlines()[-1]}")
