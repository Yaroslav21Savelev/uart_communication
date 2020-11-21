def map(x, in_min, in_max, out_min, out_max):
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min


def constrain(x, min, max):
	if x > max:
	    return max
	elif x < min:
	    return min
	else:
	    return x


class robot:
    def __init__(self, port = None):
        from serial import Serial
        from time import sleep
        #self.wire = Serial("/dev/serial0", 57600, timeout=1)
        if port is None:
            _flag = True
            while _flag:
                for i in range(30):
                    try:
                        self.wire = Serial("COM" + str(i), 57600, timeout=5)
                        print("COM" + str(i))
                        _flag = False
                        break
                    except:
                        pass
                if _flag:
                    print("retrying to connect to COM...")
                    sleep(1)
        else:
            self.wire = Serial(port, 57600, timeout=5)
            print(port)
    def write(self, ang, sp, dist):
        self.wire.write(bytes([int(ang) >> 8]))
        self.wire.write(bytes([int(ang) & 0xFF]))
        self.wire.write(bytes([int(sp) >> 8]))
        self.wire.write(bytes([int(sp) & 0xFF]))
        self.wire.write(bytes([int(dist) >> 8]))
        self.wire.write(bytes([int(dist) & 0xFF]))
