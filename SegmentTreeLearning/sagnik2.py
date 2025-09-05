from flask import Flask, jsonify, request

app = Flask(_name_)

# Core function for wedding planning
def plan_wedding(weather_condition, budget):
    try:
        # Budget validation
        if budget is None or budget == "":
            return {"error": "Budget is required"}, 400
        budget = float(budget)  # convert to numeric
        if budget < 0:
            return {"error": "Budget cannot be negative"}, 400
    except ValueError:
        return {"error": "Budget must be numeric"}, 400

    # Weather condition handling
    if not weather_condition:
        return {"error": "Weather condition is required"}, 400

    weather_condition = weather_condition.lower()

    if weather_condition == "rainy":
        plan = f"Plan an indoor wedding. Budget: {budget}"
    elif weather_condition == "sunny":
        plan = f"Plan an outdoor wedding. Budget: {budget}"
    elif weather_condition == "snowy":
        plan = f"Plan an indoor wedding with a warm ambiance. Budget: {budget}"
    else:
        return {"error": "Invalid weather condition"}, 400

    return {"plan": plan, "budget": budget}, 200


# API endpoint
@app.route('/plan_wedding', methods=['POST'])
def wedding_plan():
    data = request.get_json()

    # Missing JSON body
    if not data:
        return jsonify({"error": "Invalid request, JSON required"}), 400

    weather_condition = data.get("weather_condition")
    budget = data.get("budget")

    response, status = plan_wedding(weather_condition, budget)
    return jsonify(response), status


if _name_ == "_main_":
    app.run(debug=True)