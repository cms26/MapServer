#!/usr/bin/env python3
import datetime
import json
import common_util as util

with open('example_track.json', 'r') as fp:
    file_data = json.load(fp)

new_item = {'color': '#a103fc', 'description': file_data['desc'], 'location_history': []}

# unix timestamp in seconds since epoch (1970)
timestamp = datetime.datetime.fromtimestamp(float(file_data['timestamp']))

for loc in file_data['trace']:
    # seconds after timestamp
    track_item_time = timestamp + datetime.timedelta(seconds=int(loc[0]))
    new_item['location_history'].append(
        {
            'time_utc': track_item_time.isoformat(),
            'latitude_deg': loc[1],
            'longitude_deg': loc[2],
            'altitude_m': float(loc[3]) * 0.3048
        })

util.put_data([new_item])
