
all: image_file ascii_image questions_3 hello flag_romania ActionData.o MenuData.o ppm_menu

NumberGrid.o: NumberGrid.cpp PPM.h 
	g++ -std=c++11 -c NumberGrid.cpp

ThreadedGrid.o: ThreadedGrid.cpp NumberGrid.h 
	g++ -std=c++11 -c ThreadedGrid.cpp

MandelbrotSet.o: MandelbrotSet.cpp ComplexFractal.h
	g++ -std=c++11 -c MandelbrotSet.cpp

JuliaSet.o: JuliaSet.cpp ComplexFractal.h ThreadedGrid.h
	g++ -std=c++11 -c JuliaSet.cpp

ComplexFractal.o: ComplexFractal.cpp NumberGrid.h ThreadedGrid.h
	g++ -std=c++11 -c ComplexFractal.cpp

ColorTable.o: ColorTable.cpp 
	g++ -std=c++11 -c ColorTable.cpp

image_filters.o: image_filters.cpp image_menu.h
	g++ -std=c++11 -c image_filters.cpp

ActionData.o: ActionData.cpp ActionData.h PPM.h NumberGrid.h ColorTable.h ThreadedGrid.h
	g++ -std=c++11 -c ActionData.cpp

MenuData.o: MenuData.cpp MenuData.h ActionData.h ThreadedGrid.h
	g++ -std=c++11 -c MenuData.cpp

ppm_menu: ppm_menu.o PPM.o Image.o controllers.o image_drawing.o image_output.o user_io.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ -std=c++11 -o ppm_menu ppm_menu.o PPM.o Image.o controllers.o image_drawing.o image_output.o user_io.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

ppm_menu.o: ppm_menu.cpp image_menu.h
	g++ -std=c++11 -c ppm_menu.cpp

flag_romania: flag_romania.o PPM.o Image.o controllers.o image_drawing.o image_output.o user_io.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ -std=c++11 -o flag_romania flag_romania.o PPM.o Image.o controllers.o image_drawing.o image_output.o user_io.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

flag_romania.o: flag_romania.cpp image_menu.h PPM.h
	g++ -std=c++11 -c flag_romania.cpp

image_file: image_file.o PPM.o Image.o controllers.o image_drawing.o image_output.o user_io.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ -std=c++11 -o image_file image_file.o PPM.o Image.o controllers.o image_drawing.o image_output.o user_io.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

image_file.o: image_file.cpp image_menu.h PPM.h ActionData.h MenuData.h NumberGrid.h ThreadedGrid.h
	g++ -std=c++11 -c image_file.cpp

PPM.o: PPM.cpp PPM.h Image.h
	g++ -std=c++11 -c PPM.cpp

ascii_image: ascii_image.o Image.o controllers.o image_drawing.o image_output.o user_io.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ -std=c++11 -o ascii_image ascii_image.o Image.o controllers.o image_drawing.o image_output.o user_io.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

Image.o: Image.cpp Image.h
	g++ -std=c++11 -c Image.cpp

ascii_image.o: ascii_image.cpp image_menu.h ActionData.h MenuData.h
	g++ -std=c++11 -c ascii_image.cpp

image_drawing.o: image_drawing.cpp image_menu.h Image.h PPM.h ActionData.h NumberGrid.h ThreadedGrid.h
	g++ -std=c++11 -c image_drawing.cpp

image_output.o: image_output.cpp image_menu.h Image.h PPM.h
	g++ -std=c++11 -c image_output.cpp	

questions_3: questions_3.o controllers.o user_io.o image_drawing.o image_output.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o
	g++ -std=c++11 -o questions_3 questions_3.o controllers.o user_io.o image_drawing.o image_output.o Image.o PPM.o ActionData.o MenuData.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

questions_3.o: questions_3.cpp image_menu.h ActionData.h
	g++ -std=c++11 -c questions_3.cpp

controllers.o: controllers.cpp image_menu.h ActionData.h MenuData.h
	g++ -std=c++11 -c controllers.cpp

user_io.o: user_io.cpp image_menu.h ActionData.h
	g++ -std=c++11 -c user_io.cpp

hello: hello.o
	g++ -std=c++11 -o hello hello.o
hello.o: hello.cpp
	g++ -std=c++11 -c hello.cpp

#removes .o files and the text file versions of cpp's 
clean:
	-rm -f *.o
	-rm -f hello
	-rm -f questions_3
	-rm -f ascii_image
	-rm -f image_file
	-rm -f flag_romania
	-rm -f ppm_menu
