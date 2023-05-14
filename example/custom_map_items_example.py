import requests

url ='http://localhost/map-items/'

def get_custom_items():
    jsonItems = requests.get(url).json()
    mapItems = []
    for item in jsonItems:
        if 'Custom-' in item['id']:
            mapItems.append(item)
    return mapItems
    
def put_data(update_data):
    print('Sending', update_data)
    requests.put(url, json=update_data)

# add initial  set of map data
json_data = [{"color": "#ff0000","location_history": [{"latitude_deg": 39.4227,"longitude_deg": -77.4187,"altitude_m": 534}, {"latitude_deg": 39.5227,"longitude_deg": -77.3187,"altitude_m": 734}]}, {"color": "#499287","location_history": [{"latitude_deg": 39.2227,"longitude_deg": -77.3337,"altitude_m": 534}, {"latitude_deg": 39.6627,"longitude_deg": -77.7787,"altitude_m": 734}]}]
put_data(json_data)

mapItems = get_custom_items()

print('mapItems', mapItems)
# change the color of the first item
update_data = [{
    'id': mapItems[0]['id'],
    'color': '#34ebbd'
}]
put_data(update_data)
mapItems = get_custom_items()

# update the description of the first item
update_data = [{
    'id': mapItems[0]['id'],
    'description': 'Some sort of description that is pretty detailed with info.'
}]
put_data(update_data)


# update the description of the first item
update_data = [{
    'id': mapItems[0]['id'],
    'description': '<html><b>A-Value:</b> 1234<br><b>B-Value:</b> 4566<br><b>C-Value:</b> 954</html>'
}]
put_data(update_data)

# add location to second item
update_data = [{
    'id': mapItems[1]['id'],
    'location_history': [{"latitude_deg": 39.649422,"longitude_deg": -79.965622}],
    'description': 'I moved to Morgantown, WV!'
}]
put_data(update_data)