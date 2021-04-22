# SEARCHING ALGORITHMS SERVER
This program was created in Advance Programing course in Bar-Ilan University,
on 2020.


# AUTHORS
   - Reut Berger (reutbrgr@gmail.com)
   - Eden Simony (shimone5@macs.biu.ac.il)


# INTRODUCTION
The project has been written on CLion environment, in C++.
We worked together on the project and we learned a lot about how to use several designs patterns.


# DESCRIPTION
The project opens a server that handles up to 12 clients in parallel.
Each client sends a problem (a matrix with a starting point and ending point) and the server solve it and return the
solution back to the client.
But before solving the problem, the server will check if a solution to this specific problem already exists in the directory.
If does - it will send it to the client. else - the server will solve the problem and send the solution back to the client.
Solving the problem is done by four algorithms:
- Best First Search
- BFS
- DFS
- A* (A Star)
We tested all four algorithms and we found that the A Star is the best algorithm
(considering the path length and the cost of each path).
Therefore, in the main function we made the parallel server use the A Star algorithm to solve the client's problems.

*The project also support a serial server that handles each client at a time.
*For your comfort, you can find examples for ten different matrix problem in file "AllMatrixInTrail.txt".


# RUN PROJECT
   - Compile the project in terminal (on linux) with command:
     g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread

   - Run the out file with command:
     ./a.out port
     ("port" is the port number that the server will work on)

   - The server will wait for client's connections and will send back data.
   - If after two minutes no client will connect, the server will close.

