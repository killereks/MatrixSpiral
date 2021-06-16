#include <iostream>
#include <cstring>

bool ShouldChangeDirection(int x, int y, int NumRows, int NumColumns, bool seen[], int size) {
    int index = x + y * NumColumns;
    // if we are outside of the array
    // we should change direction
    if (x >= NumColumns) return true;
    if (x < 0) return true;

    if (index < 0 || index > size){
        return true;
    }
    // we are inside array
    return seen[index];
}

void SetDirection(int *x, int *y, int direction){
    if (direction == 0){
        *x = 1;
        *y = 0;
    } else if (direction == 1){
        *x = 0;
        *y = 1;
    } else if (direction == 2){
        *x = -1;
        *y = 0;
    } else {
        *x = 0;
        *y = -1;
    }
}

void BuildStringFromMatrix(int* Matrix, int NumRows, int NumColumns, char* OutBuffer){
    if (sizeof(Matrix) == 0){
        return;
    }

    int elementCount = NumRows * NumColumns;
    // elements we have already seen
    bool seen[elementCount];
    for (int i = 0; i < elementCount; i++){
        seen[i] = false;
    }
    // direction in x and y
    int dx = 1;
    int dy = 0;
    // position in x and y
    int px = 0;
    int py = 0;

    int direction = 0; // 0 = right, 1 = down, 2 = left, 3 = up

    std::string answer;

    for (int i = 0; i < elementCount; i++){
        // 2D index to 1D index
        int index = py * NumColumns + px;
        // store answer as a string
        answer += std::to_string(Matrix[index])+" ";

        seen[index] = true;

        int nextX = px + dx;
        int nextY = py + dy;
        // if our next element is outside
        // of the matrix, we should just change
        // the direction now
        bool hasSeenNext = ShouldChangeDirection(nextX, nextY, NumRows, NumColumns, seen, elementCount);

        if (hasSeenNext){
            direction = (direction + 1) % 4;

            SetDirection(&dx, &dy, direction);
        }
        
        px += dx;
        py += dy;
    }

    std::strcpy(OutBuffer, answer.c_str());
}

int main(){
    int matrix[] = {2,3,4,8,5,7,9,12,1,0,6,10};

    char out[20];

    BuildStringFromMatrix(matrix, 3, 4, out);

    std::cout << out;

    return 0;
}