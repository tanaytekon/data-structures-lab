#include <iostream>
#include <fstream>
using namespace std;

// Declaraiton of variables in global scope
int** mapMatrix;
int** keyMatrix;
int* mapSize;
int keySize;
int keyCenterIndex;
ofstream outputFile;

/**
 * Splits the given string to the integer array with given delimiter.
 * @param str String to be splitted.
 * @param intArr The array which will be modified.
 * @param arrSize Size of the created array.
 * @param del Delimitter character.
*/
void stringToIntArray(string str, int* &intArr, int arrSize, char del);

/**
 * Splits the data in given file to the integer matrix.
 * @param fileName Name of the matrix file.
 * @param matrix The matrix array which will be modified.
 * @param matrixSize Size of the matrix that will be created.
*/
void splitToMatrix(string fileName, int** &matrix, int* &matrixSize);

/**
 * Searches map matrix for treasure with given key matrix.
 * @param action Integer value of direction.
 * @param position An integer array which stores the index of current position(top left corner of sub matrix).
 * @param result Result of the dot product.
*/
void search(int &action , int* &position, int &result);


int main(int argc, char *argv[]) {
	
	// Obtaining arguments from command line and initializing variables
	stringToIntArray(argv[1], mapSize, 2, 'x');
    keySize = stoi(argv[2]);

	int* keyMatrixSize = new int[2];
	keyMatrixSize[0] = keyMatrixSize[1] = keySize;
	
    splitToMatrix(argv[4], keyMatrix, keyMatrixSize);
    delete[] keyMatrixSize;
	splitToMatrix(argv[3], mapMatrix, mapSize);
	
    int* position = new int[2];
    position[0] = position[1] = 0;

    int action = -1;
    int result = 0;
    keyCenterIndex = (keySize - 1)/2;
    outputFile.open(argv[5]);

    search(action, position, result);

    // Deallocating the memory
    delete[] position;

    for(int i=0; i<mapSize[0]; i++) {
        delete[] mapMatrix[i];
    }
    delete[] mapMatrix;
    delete[] mapSize;

    for(int i=0; i<keySize; i++) {
        delete[] keyMatrix[i];
    }
    delete[] keyMatrix;

    outputFile.close();

	return 0;
}


void stringToIntArray(string str, int* &intArr, int arrSize, char del) {
	intArr = new int[arrSize];
	str += del;
	string tempStr;
	int counter = 0;
	for (char c : str) {
		if (c != del) {
			tempStr += c;
		}
		else {
			intArr[counter++] = stoi(tempStr);
			tempStr = "";
		}
	}
}


void splitToMatrix(string fileName, int** &matrix, int* &matrixSize) {
	
    // Initializing variables
	ifstream matrixFile(fileName);
	int rowSize = matrixSize[0];
	int columnSize = matrixSize[1];
	
	// Creating a dynamic array
	matrix = new int*[rowSize];
	
	// Initializing matrix
	string line;
	int lineCounter = 0;
    // Reading matrix from file line by line and conveting to integer array
	while (getline (matrixFile, line)) {
		stringToIntArray(line, matrix[lineCounter++], columnSize, ' ');
	}
	
	matrixFile.close();
}


void search(int &action , int* &position, int &result) {
	
    // Base case
    if (action == 0) {
        // Writes final step to the output file and ends recursion
        outputFile << position[0]+keyCenterIndex << ',' << position[1]+keyCenterIndex << ':' << result;
		return;
	}

    // Calculates dot product of sub matrix and key matrix
    result = 0;
    for (int row = 0; row < keySize; row++) {
        for (int column = 0; column < keySize; column++) {
            result += (mapMatrix[position[0]+row][position[1]+column] * keyMatrix[row][column]);
        }
    }
    
    while (result < 0) {
        result  += 5;
    }

    // Determination of direction value(action) and winnig condition
    // Handling the exception for the estimated direction
    action = result % 5;
    if (action != 0) {
        // Writes this step to the output file
        outputFile << position[0]+keyCenterIndex << ',' << position[1]+keyCenterIndex << ':' << result << endl;
    }
    while(action != 0) {
        if (action == 1) { //Go up
            if (position[0]-keySize < 0) { // If on boundary, change direction
                action = 2;
            }
            else {
                position[0] -= keySize;
                break;
            }
        }
        else if (action == 2) { //Go down
            if (position[0] + keySize > mapSize[0]-keySize) { // If on boundary, change direction
                action = 1;
            }
            else {
                position[0] += keySize;
                break;
            }
        }
        else if (action == 3) { //Go right
            if (position[1] + keySize> mapSize[1]-keySize) { // If on boundary, change direction
                action = 4;
            }
            else {
                position[1] += keySize;
                break;
            }
        }
        else if (action == 4) { //Go left
            if (position[1]-keySize < 0) { // If on boundary, change direction
                action = 3;
            }
            else {
                position[1] -= keySize;
                break;
            }
        }
    }
	search(action, position, result);
}