# Pass the video name, without the extension. Must be the filename only, not the path!
ffmpeg -i $1.mp4 -qscale:v 25 frame%03d.jpg
zip -9 $1.zip frame*.jpg
rm frame*.jpg