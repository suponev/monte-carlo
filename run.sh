clear && mpicc -o main main.c -lm && mpirun -np 4 ./main 
#--allow-run-as-root
#mpirun -np 4 ./a.out