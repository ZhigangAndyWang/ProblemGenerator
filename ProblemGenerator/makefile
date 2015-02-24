obj= RandomPackage.o TypeDefinition.o GeneralProblem.o ProblemGenerator.o\
 MultipleChoiceProblem.o MultipleChoiceGenerator.o\
  ReadingProblem.o ReadingGenerator.o

Debug/out: $(obj)
	g++ -o $@ $(obj)
RandomPackage.o: RandomPackage.cpp RandomPackage.h
	g++ -c $<
TypeDefinition.o: TypeDefinition.cpp TypeDefinition.h
	g++ -c $<
GeneralProblem.o: GeneralProblem.cpp GeneralProblem.h \
                  MultipleChoiceGenerator.h ReadingGenerator.h
	g++ -c $<
ProblemGenerator.o: ProblemGenerator.cpp GeneralProblem.h
	g++ -c $<
MultipleChoiceProblem.o: MultipleChoiceProblem.cpp \
                           MultipleChoiceProblem.h \
			   RandomPackage.h TypeDefinition.h
	g++ -c $<
MultipleChoiceGenerator.o: MultipleChoiceGenerator.cpp \
               MultipleChoiceGenerator.h MultipleChoiceProblem.h
	g++ -c $<
ReadingGenerator.o: ReadingGenerator.cpp ReadingGenerator.h \
                    ReadingProblem.h
	g++ -c $<
ReadingProblem.o: ReadingProblem.cpp ReadingProblem.h \
                  RandomPackage.h TypeDefinition.h
	g++ -c $<
clean:
	-rm *.o ; -rm Debug/out 
