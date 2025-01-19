# API FOR LOCATION

from googlemaps import Client

def get_place_details(api_key, place_id):

  try:
    gmaps = Client(key=api_key)
    place_details = gmaps.place_details(place_id=place_id)
    return place_details

  except Exception as e:
    print(f"Error fetching place details: {e}")
    return None

place_details = get_place_details(api_key, place_id)

if place_details:

  name = place_details.get('result', {}).get('name')
  address = place_details.get('result', {}).get('formatted_address')
  location = place_details.get('result', {}).get('geometry', {}).get('location') 

  print(f"Name: {name}")
  print(f"Address: {address}")
  print(f"Location: {location}")

# API FOR FINDING PATHS

from googlemaps import Client

def get_route(api_key, origin, destination, travel_mode='driving'):

  try:
    gmaps = Client(key=api_key)
    directions_result = gmaps.directions(origin, destination, mode=travel_mode)
    return directions_result[0]  # Return the first route found

  except Exception as e:
    print(f"Error fetching route: {e}")
    return None

route = get_route(api_key, origin, destination)

if route:

  distance = route['legs'][0]['distance']['text']
  duration = route['legs'][0]['duration']['text']
  overview_polyline = route['overview_polyline']['points'] 

  print(f"Distance: {distance}")
  print(f"Duration: {duration}")
  print(f"Overview Polyline: {overview_polyline}")

# API FOR CONVERTING ADDRESSES TO CO-ORDINATES

from googlemaps import Client

def address_to_coordinates(api_key, address):
 
  try:
    gmaps = Client(key=api_key)
    geocode_result = gmaps.geocode(address)

    if geocode_result:
      location = geocode_result[0]['geometry']['location']
      return {'lat': location['lat'], 'lng': location['lng']}
    else:
      return None 

  except Exception as e:
    print(f"Error geocoding address: {e}")
    return None


coordinates = address_to_coordinates(api_key, address)

if coordinates:
  print(f"Latitude: {coordinates['lat']}")
  print(f"Longitude: {coordinates['lng']}")

# API FOR ACTUAL MAPS

from flask import Flask, request, jsonify
from googlemaps import Client

app = Flask(__name__)

API_KEY = "YOUR_GOOGLE_MAPS_API_KEY" 
gmaps = Client(key=API_KEY)

@app.route('/geocode', methods=['GET'])
def geocode():

  address = request.args.get('address')
  if not address:
    return jsonify({'error': 'Address parameter is required'}), 400

  try:
    geocode_result = gmaps.geocode(address)
    if geocode_result:
      location = geocode_result[0]['geometry']['location']
      return jsonify({'lat': location['lat'], 'lng': location['lng']})
    else:
      return jsonify({'error': 'Address not found'}), 404
  except Exception as e:
    return jsonify({'error': str(e)}), 500

@app.route('/distance', methods=['GET'])
def distance():

  origin = request.args.get('origin')
  destination = request.args.get('destination')
  if not origin or not destination:
    return jsonify({'error': 'Origin and destination parameters are required'}), 400

  try:
    directions_result = gmaps.directions(origin, destination)
    if directions_result:
      distance = directions_result[0]['legs'][0]['distance']['text']
      return jsonify({'distance': distance})
    else:
      return jsonify({'error': 'Route not found'}), 404
  except Exception as e:
    return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
  app.run(debug=True)