sudo apt-get install freeglut3-dev
gcc algorithms.c -lGL -lGLU -lglut -o algorithms.out
gcc fractals.c -lm -lGL -lGLU -lglut -o fractals.out
./fractals.out
./algorithms.out
