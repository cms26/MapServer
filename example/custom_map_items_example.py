#!/usr/bin/env python3
import common_util as util

# add initial  set of map data
json_data = [{"color": "#ff0000",
              "location_history": [{"latitude_deg": 39.4227, "longitude_deg": -77.4187, "altitude_m": 534, "time_utc": "2023-05-25T13:10:06"},
                                   {"latitude_deg": 39.5227, "longitude_deg": -77.3187, "altitude_m": 734, "time_utc": "2023-05-25T13:11:00"}]},
             {"color": "#499287",
              "location_history": [{"latitude_deg": 39.2227, "longitude_deg": -77.3337, "altitude_m": 534, "time_utc": "2023-05-25T13:11:13"},
                                   {"latitude_deg": 39.6627, "longitude_deg": -77.7787, "altitude_m": 734, "time_utc": "2023-05-25T13:11:33"}]}]
util.put_data(json_data)
mapItems = util.get_custom_items()

# change the color of the first item
update_data = [{
    'id': mapItems[0]['id'],
    'color': '#34ebbd'
}]
util.put_data(update_data)
mapItems = util.get_custom_items()

# update the description of the first item
update_data = [{
    'id': mapItems[0]['id'],
    'description': 'Some sort of description that is pretty detailed with info.'
}]
util.put_data(update_data)

# update the description of the first item
update_data = [{
    'id': mapItems[0]['id'],
    'description': '<html><b>A-Value:</b> 1234<br><b>B-Value:</b> 4566<br><b>C-Value:</b> 954</html>'
}]
util.put_data(update_data)

# add location to second item
update_data = [{
    'id': mapItems[1]['id'],
    'location_history': [{"latitude_deg": 39.649422, "longitude_deg": -79.965622, "altitude_m": 365, "time_utc": "2023-05-25T13:12:06"}],
    'description': 'I moved to Morgantown, WV!'
}]
util.put_data(update_data)
