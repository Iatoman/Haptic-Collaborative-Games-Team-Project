#include "Map.h"

Map::Map(int row, int col) {
    this->rows = row;
    this->cols = col;
    this->grid = new int*[row];
    for(int i = 0; i < row; i++) {
		grid[i] = new int[col];
	}
}

Map::~Map() {
    for(int i = 0; i < rows; i++) {		
		delete[] grid[i];
	}
    delete[] grid;
}

/**
 * @brief A Utility Function to set start point
 *     
 * 
 * @param row row that start point is in
 * @param col column that start point is in
 */
void Map::setSource(int row, int col) {
    this->src = make_pair(row, col);
}

/**
 * @brief A Utility Function to set destination point
 *     
 * 
 * @param row row that destination point is in
 * @param col column that destination point is in
 */
void Map::setDestination(int row, int col) {
    this->dest = make_pair(row, col);
}

/**
 * @brief A Utility Function to set grid of map
 *     
 * 
 * @param grids pointer of grid
 */
void Map::setGrid(int **grids) { 
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->grid[i][j] = grids[i][j];
		}
    }
}

/**
 * @brief A Utility Function to get optimal path
 *     
 * 
 * @return path whole optimal path through AI algorithm
 */
stack<Pair> Map::getPath() {
    return this->path;
}

/**
 * @brief A Utility Function to check whether given cell (row, col) is a valid cell or not
 * 
 * @param row row of grid
 * @param col column of grid
 * 
 * @return boolean value true if row number and column number is in range, otherwise, false
 */
bool Map::isValid(int row, int col) const {
    return (row >= 0) && (row < rows) && (col >= 0) && (col < cols);
}

/**
 * @brief A Utility Function to check whether the given cell is blocked or not
 * 
 * @param row row that the current cell is in
 * @param col column that the current cell is in    
 * 
 * @return boolean value true if the cell is not blocked, otherwise, false
 */
bool Map::isUnBlocked(int row, int col) {
    if(grid[row][col] == 1)
        return (true);
    else
        return (false);
}

/**
 * @brief A Utility Function to check whether destination cell has been reached or not
 *
 * @param row row that the current cell is in
 * @param col column that the current cell is in     
 * 
 * @return boolean value true if the destination cell has been reached, otherwise, false
 */
bool Map::isDestination(int row, int col) const {
    if(row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

/**
 * @brief A Utility Function to calculate the 'h' heuristics
 *
 * @param row row that the current cell is in
 * @param col column that the current cell is in     
 * 
 * @return distance using the Euclidean distance formula
 */
double Map::calculateHValue(int row, int col) const {
    return ((double)sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
}

/**
 * @brief A Utility Function to trace the path from the source to destination
 *
 * @param cellDetails pointer of the current cell
 */
void Map::tracePath(cell **cellDetails) {
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;
    cellDetails[row][col].symbol = 'D';

    stack<Pair> Path;

    while(!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;

        // record the path direction in the cellDetails
        if(temp_row != -1 && temp_col != -1) {
            if(temp_row - row != 0 && temp_col == col) cellDetails[temp_row][temp_col].symbol = '|';
            if(temp_row == row && temp_col - col != 0) cellDetails[temp_row][temp_col].symbol = '-';
            if((temp_row - row) * (temp_col - col) > 0) cellDetails[temp_row][temp_col].symbol = '\\';
            if((temp_row - row) * (temp_col - col) < 0) cellDetails[temp_row][temp_col].symbol = '/';
        }
        row = temp_row;
        col = temp_col;
    }
    cellDetails[row][col].symbol = 'S';

    Path.push(make_pair(row, col));

    this->path = Path;

    while(!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
    }
    printf("\n");

    for(int j = 0; j < cols; j++) {
        printf(".-. ");
    }
	printf("\n");
	
    for(int i = 0; i < rows; i++) {
        if(i > 0) {
            for(int j = 0; j < cols; j++) {
                printf(":-: ");
            } 
		    printf("\n");
        }

        for(int j = 0; j < cols; j++) {
            printf("|%c| ", cellDetails[i][j].symbol);
        } 
		printf("\n");
    }
	
    for(int j = 0; j < cols; j++) {
        printf("'-' ");
    } 
	printf("\n");
}

/**
 * @brief A Utility Function to find the shortest path between source cell to destination cell based on A* Search Algorithm
 */
void Map::aStarSearch() {
    // If the source is out of range
    if(!isValid(src.first, src.second)) {
        printf("Source is invalid\n");
        return;
    }

    // If the destination is out of range
    if(!isValid(dest.first, dest.second)) {
        printf("Destination is invalid\n");
        return;
    }

    // Either the source or the destination is blocked
    if(!isUnBlocked(src.first, src.second) || !isUnBlocked(dest.first, dest.second)) {
        printf("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell
    if(isDestination(src.first, src.second)) {
        printf("We are already at the destination\n");
        return;
    }

    // Create a closed list and initialise it to false which means that no cell has been included yet. 
    // This closed list is implemented as a boolean 2D array
    bool closedList[rows][cols];
    memset(closedList, false, sizeof(closedList));

    // Declare a 2D array of structure to hold the details of that cell
    cell cellDetails[rows][cols];
    cell *cellDetails_p[rows];
    for(int i = 0; i < rows; i++) {
        cellDetails_p[i] = cellDetails[i];
    }

    int i, j;

    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++){
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
            cellDetails[i][j].symbol = grid[i][j] == 1 ? ' ' : 'o';
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    /*
     Create an open list having information as- <f, <i, j>>
     where f = g + h, and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implemented as a set of pair of pair.
	 */
    set<pPair> openList;

    // Put the starting cell on the open list and set its 'f' as 0
    openList.insert(make_pair(0.0, make_pair(i, j)));

    // We set this boolean value as false as initially the destination is not reached.
    bool foundDest = false;

    while(!openList.empty()) {
        pPair p = *openList.begin();

        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        /*
         Generating all the 8 successor of this cell

             N.W   N   N.E
               \   |   /
                \  |  /
             W----Cell----E
                  / | \
                /   |  \
             S.W    S   S.E

         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)
         N.E--> North-East  (i-1, j+1)
         N.W--> North-West  (i-1, j-1)
         S.E--> South-East  (i+1, j+1)
         S.W--> South-West  (i+1, j-1)
		 */

        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------
        // Only process this cell if this is a valid one
        if(isValid(i - 1, j)) {
            // If the destination cell is the same as the current successor
            if(isDestination(i - 1, j)) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails_p);
                foundDest = true;
                return;
            }
			// If the successor is already on the closed list
			// or if it is blocked, then ignore it.
			// Else do the following
            else if(!closedList[i - 1][j] && isUnBlocked(i - 1, j)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j);
                fNew = gNew + hNew;
                // If it isn’t on the open list, add it to the open list. 
				// Make the current square the parent of this square. 
				// Record the f, g, and h costs of the square cell or
                // if it is on the open list already, 
				// check to see if this path to that square is better, using 'f' cost as the measure.
                if(cellDetails[i - 1][j].f == FLT_MAX || cellDetails[i - 1][j].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j)));
                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------
        // Only process this cell if this is a valid one
        if(isValid(i + 1, j)) {
            // If the destination cell is the same as the current successor
            if(isDestination(i + 1, j)) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails_p);
                foundDest = true;
                return;
            }
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
            else if(!closedList[i + 1][j] && isUnBlocked(i + 1, j)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j);
                fNew = gNew + hNew;
				// If it isn’t on the open list, add it to the open list. 
				// Make the current square the parent of this square. 
				// Record the f, g, and h costs of the square cell or
                // if it is on the open list already, 
				// check to see if this path to that square is better, using 'f' cost as the measure.
                if(cellDetails[i + 1][j].f == FLT_MAX || cellDetails[i + 1][j].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j)));
                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------
        // Only process this cell if this is a valid one
        if(isValid(i, j + 1)) {
            // If the destination cell is the same as the current successor
            if(isDestination(i, j + 1)) {
                // Set the Parent of the destination cell
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails_p);
                foundDest = true;
                return;
            }
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
            else if(!closedList[i][j + 1] && isUnBlocked(i, j + 1)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1);
                fNew = gNew + hNew;
                // If it isn’t on the open list, add it to the open list. 
				// Make the current square the parent of this square. 
				// Record the f, g, and h costs of the square cell or
                // if it is on the open list already, 
				// check to see if this path to that square is better, using 'f' cost as the measure.
                if(cellDetails[i][j + 1].f == FLT_MAX || cellDetails[i][j + 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i, j + 1)));
                    // Update the details of this cell
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------
        // Only process this cell if this is a valid one
        if(isValid(i, j - 1)) {
            // If the destination cell is the same as the current successor
            if(isDestination(i, j - 1)){
                // Set the Parent of the destination cell
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails_p);
                foundDest = true;
                return;
            }

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
            else if (!closedList[i][j - 1] && isUnBlocked(i, j - 1)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1);
                fNew = gNew + hNew;
                // If it isn’t on the open list, add it to the open list. 
				// Make the current square the parent of this square. 
				// Record the f, g, and h costs of the square cell or
                // if it is on the open list already, 
				// check to see if this path to that square is better, using 'f' cost as the measure.
                if (cellDetails[i][j - 1].f == FLT_MAX || cellDetails[i][j - 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i, j - 1)));
                    // Update the details of this cell
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

        //----------- 5th Successor (North-East) ------------
        // Only process this cell if this is a valid one
        if(isValid(i - 1, j + 1)) {
            // If the destination cell is the same as the current successor
            if(isDestination(i - 1, j + 1)) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j + 1].parent_i = i;
                cellDetails[i - 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails_p);
                foundDest = true;
                return;
            }
			// If the successor is already on the closed list
			// or if it is blocked, then ignore it.
			// Else do the following
            else if(!closedList[i - 1][j + 1] && isUnBlocked(i - 1, j + 1)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j + 1);
                fNew = gNew + hNew;
                // If it isn’t on the open list, add it to the open list. 
				// Make the current square the parent of this square. 
				// Record the f, g, and h costs of the square cell or
                // if it is on the open list already, 
				// check to see if this path to that square is better, using 'f' cost as the measure.
                if(cellDetails[i - 1][j + 1].f == FLT_MAX || cellDetails[i - 1][j + 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j + 1)));
                    // Update the details of this cell
                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                }
            }
        }

        //----------- 6th Successor (North-West) ------------
        // Only process this cell if this is a valid one
        if(isValid(i - 1, j - 1)) {
            // If the destination cell is the same as the current successor
            if(isDestination(i - 1, j - 1)) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j - 1].parent_i = i;
                cellDetails[i - 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails_p);
                foundDest = true;
                return;
            }
			// If the successor is already on the closed list
			// or if it is blocked, then ignore it.
			// Else do the following
            else if(!closedList[i - 1][j - 1] && isUnBlocked(i - 1, j - 1)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j - 1);
                fNew = gNew + hNew;
                // If it isn’t on the open list, add it to the open list. 
				// Make the current square the parent of this square. 
				// Record the f, g, and h costs of the square cell or
                // if it is on the open list already, 
				// check to see if this path to that square is better, using 'f' cost as the measure.
                if(cellDetails[i - 1][j - 1].f == FLT_MAX || cellDetails[i - 1][j - 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));
                    // Update the details of this cell
                    cellDetails[i - 1][j - 1].f = fNew;
                    cellDetails[i - 1][j - 1].g = gNew;
                    cellDetails[i - 1][j - 1].h = hNew;
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                }
            }
        }

        //----------- 7th Successor (South-East) ------------
        // Only process this cell if this is a valid one
        if(isValid(i + 1, j + 1)) {
            // If the destination cell is the same as the current successor
            if(isDestination(i + 1, j + 1)) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j + 1].parent_i = i;
                cellDetails[i + 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails_p);
                foundDest = true;
                return;
            }
			// If the successor is already on the closed list
			// or if it is blocked, then ignore it.
			// Else do the following
            else if(!closedList[i + 1][j + 1] && isUnBlocked(i + 1, j + 1)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j + 1);
                fNew = gNew + hNew;
                // If it isn’t on the open list, add it to the open list. 
				// Make the current square the parent of this square. 
				// Record the f, g, and h costs of the square cell or
                // if it is on the open list already, 
				// check to see if this path to that square is better, using 'f' cost as the measure.
                if(cellDetails[i + 1][j + 1].f == FLT_MAX || cellDetails[i + 1][j + 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j + 1)));
                    // Update the details of this cell
                    cellDetails[i + 1][j + 1].f = fNew;
                    cellDetails[i + 1][j + 1].g = gNew;
                    cellDetails[i + 1][j + 1].h = hNew;
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                }
            }
        }

        //----------- 8th Successor (South-West) ------------
        // Only process this cell if this is a valid one
        if(isValid(i + 1, j - 1)) {
            // If the destination cell is the same as the current successor
            if(isDestination(i + 1, j - 1)) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j - 1].parent_i = i;
                cellDetails[i + 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails_p);
                foundDest = true;
                return;
            }
			// If the successor is already on the closed list
			// or if it is blocked, then ignore it.
			// Else do the following
            else if(!closedList[i + 1][j - 1] && isUnBlocked(i + 1, j - 1)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j - 1);
                fNew = gNew + hNew;
                // If it isn’t on the open list, add it to the open list. 
				// Make the current square the parent of this square. 
				// Record the f, g, and h costs of the square cell or
                // if it is on the open list already, 
				// check to see if this path to that square is better, using 'f' cost as the measure.
                if(cellDetails[i + 1][j - 1].f == FLT_MAX || cellDetails[i + 1][j - 1].f > fNew) {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j - 1)));
                    // Update the details of this cell
                    cellDetails[i + 1][j - 1].f = fNew;
                    cellDetails[i + 1][j - 1].g = gNew;
                    cellDetails[i + 1][j - 1].h = hNew;
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                }
            }
        }
    }
    // When the destination cell is not found and the open list is empty, 
	// then we conclude that we failed to reach the destination cell. 
	// This may happen when there is no way to destination cell (due to blockages)
    printf("Failed to find the Destination Cell\n");
}

/**
 * @brief A Utility Function to find the next position based on the given start point
 *
 * @param src_r x-coordinate of start point
 * @param src_c y-coordinate of start point
 *
 * @return <int, int> coordinate of next position
 */
pair<int, int> Map::nextPos(int src_r, int src_c) {
    setSource(src_r, src_c);
    setDestination(DEST_R, DEST_C);
    int *grid_p[ROW];
    for(int i = 0; i < ROW; i++) {
        grid_p[i] = Grid[i];
    }
    setGrid(grid_p);
	aStarSearch();
    stack<Pair> path = getPath();
    path.pop();
    pair<int, int> p = path.top();
    return p;
}

/**
 * @brief This function maps (x, y) coordinate to index of 2d array
 * 
 * @note text
 * 
 * @param x x-coordinate
 * @param y y-coordinate
 * @return pair<Int, Int> 
 */
pair<int, int> Map::calcPos(double x, double y)
{
    // properties of game board
    double length = 2.5;

    // number of divisions
    int division = 25;

    int xi, yi;
    xi = (int) floor(division / 2.0 - division * (y / length));
    yi = (int) floor(division / 2.0 + division * (x / length));

    return {xi, yi};
}

/**
 * @brief This function maps index of 2d array to (x, y) coordinate
 * 
 * @note text
 * 
 * @param row row of 2d array
 * @param col column of 2d array
 * @return pair<double, double> 
 */
pair<double, double> Map::resPos(int row, int col)
{
    // properties of game board
    double length = 2.5;

    // number of divisions
    int division = 25;

    double x, y;
    y = length / division * (division / 2.0 - (row + 0.5));
    x = length / division * ((col + 0.5) - division / 2.0);

    return {x, y};
}

/**
 * @brief return the next position on the optimal path according to the current haptic cursor position
 * 
 * @param currentPos            ball position / haptic cursor position
 * @return chai3d::cVector3d    next position on the optimal path
 */
chai3d::cVector3d Map::findNextPos(chai3d::cVector3d currentPos) {
    pair<int, int> pos2d = calcPos(currentPos.x(), currentPos.y());
    auto nextIntPos2d = nextPos(pos2d.first, pos2d.second);
    auto nextDoublePos2d = resPos(nextIntPos2d.first, nextIntPos2d.second);
    chai3d::cVector3d nextPoint(nextDoublePos2d.first, nextDoublePos2d.second, 0);
	return nextPoint;
}