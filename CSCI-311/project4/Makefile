# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Targets for all questions
TARGETS = Q1A Q1B Q2A Q2B Q3A Q3B Q4A Q4B Q5A Q5B #Q4AA Q4BB

# Default target
all: $(TARGETS)

# Individual targets for each question
Q1A: Question1A.cpp
	$(CXX) $(CXXFLAGS) Question1A.cpp -o Q1A

Q1B: Question1B.cpp
	$(CXX) $(CXXFLAGS) Question1B.cpp -o Q1B

Q2A: Question2A.cpp
	$(CXX) $(CXXFLAGS) Question2A.cpp -o Q2A

Q2B: Question2B.cpp
	$(CXX) $(CXXFLAGS) Question2B.cpp -o Q2B

Q3A: Question3A.cpp
	$(CXX) $(CXXFLAGS) Question3A.cpp -o Q3A

Q3B: Question3B.cpp
	$(CXX) $(CXXFLAGS) Question3B.cpp -o Q3B

Q4A: Question4A.cpp
	$(CXX) $(CXXFLAGS) Question4A.cpp -o Q4A
	

Q4B: Question4B.cpp
	$(CXX) $(CXXFLAGS) Question4B.cpp -o Q4B
	

Q5A: Question5A.cpp
	$(CXX) $(CXXFLAGS) Question5A.cpp -o Q5A

Q5B: Question5B.cpp
	$(CXX) $(CXXFLAGS) Question5B.cpp -o Q5B



#Q4AA: 4A.cpp
#	$(CXX) $(CXXFLAGS) 4A.cpp -o Q4AA

#Q4BB: 4B.cpp
#	$(CXX) $(CXXFLAGS) 4B.cpp -o Q4BB
	


# Clean target to remove compiled files
clean:
	rm -f $(TARGETS)

# Run targets for each question
run: Q1B Q1A
	@echo "running Matrix Chain Multiplication"
	./Q1A
	./Q1B
	@echo "running Rod Cutting Problem"
	./Q2A
	./Q2B
	@echo "running Word Break Problem"
	./Q3A
	./Q3B
	@echo "running Partition Problem"
	./Q4A
	./Q4B
#	./Q4AA
#	./Q4BB
	@echo "running Palindrome Partitioning"
	./Q5A
	./Q5B