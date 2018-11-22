## Raspberry PI 3 - Camera miltiplexer

Load kernel module:

```bash
sudo modprobe bcm2835-v4l2
sudo v4l2-ctl -d 0 -p 90
```