#-------------
#   Allegro
#-------------
#Compiling and executing a file <nom_fichier.cpp> with Allegro
#command : ./CompileExecute.sh <nom_fichier>

clear && printf '\e[3J' ;

compile=false;

if [ $1 ]; then 
   # compilation
   g++ $1.cpp -o $1.o -lallegro -lallegro_main -lallegro_primitives -lallegro_font
   if [ $? -eq 0 ]; then
     echo "\033[36mCompilation successful  :)\033[0m"
     ./$1.o # execution
   else
     echo "\033[31mCompilation failed !!!!!!\033[0m"
   fi
else 
   echo "\033[38;5;208mErreur nom du fichier manquant (sans extension .cpp) : ./compileExecute.sh <nom_fichier>\033[0m"
fi