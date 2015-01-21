import json
import sys
import struct
from   decimal import *


if len(sys.argv) == 2:
	f = open(sys.argv[1])
	str = f.read()
	tab = json.loads(str)
	ret = struct.pack("IIII", tab['width'], tab['height'], len(tab['layers'][3]["objects"]), len(tab['tilesets'][0]['tiles']))
	for c in tab['layers'][0]['data']:
		ret = ret + unichr(c - 1)
	for c in tab['layers'][1]['data']:
		ret = ret + unichr(c - 1)
	for c in tab['layers'][2]['data']:
		ret = ret + unichr(c - 1)
	sys.stdout.write(ret)
	for obj in tab['layers'][3]['objects']:
		x = Decimal(obj["x"]) / Decimal(tab["tilewidth"])
		y = Decimal(obj["y"]) / Decimal(tab["tileheight"])
		sys.stdout.write(struct.pack("ff", x, y))
		tmp = int(obj["properties"]["type"])
		tmp2 = int((obj["properties"]["text"]))
		print(struct.pack("II" ,tmp, tmp2))
