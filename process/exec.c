#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main() 
{
	//goal is to execute ls using different variation of 
	//execv and the differences in usage
    printf("Original process started. PID: %d\n", getpid());
    printf("Attempting to execute new program (ls -l /tmp)...\n\n");
    
        // --- ARGUMENTS as a LIST (l) ---//
	
	//int execl(const char *pathname, const char *arg, ...,(char *)NULL); 
	//first argument path to executable, next arguments are
	//null terminated array of strings.  
        // 1. execl: Requires FULL PATH, NO environment control.
    	
   // execl("/bin/ls", "ls", "-l", "/tmp", (char *)NULL);
	
    	//searches in $PATH variable for executable of ls and then 
	//run this array of strings. still null terminated but here 
	//were are not specifying path to search the executable.
	//TODO => type $PATH then enter see all paths
    	// 2. execlp: Searches PATH (p), Arguments as a LIST (l).
	
   // execlp("ls", "ls", "-l", "/tmp", (char *)NULL);
	
    	
    	// 3. execle: Requires FULL PATH, Explicit ENVIRONMENT (e).
    	// Note: 'env' command is used here to show the new environment.
    char *new_env[] = {"GREETING=HelloFromExecle", "PATH=/bin:/usr/bin", NULL};
    	
     execle("/usr/bin/env", "env", (char *)NULL, new_env);


    // --- ARGUMENTS as a VECTOR/ARRAY (v) ---
    
    // Define the arguments array once for the 'v' variants.
    char *argv_list[] = {"ls", "-l", "/tmp", NULL};

    //execv needs first argument to executable, 
    //second argument is arrays of string where first string is the executable itself then arguments to it
    // 4. execv: Requires FULL PATH, Arguments as a VECTOR (v).
    
    // execv("/bin/ls", argv_list);
	
    //execvp searches default path variable to find ls,
    // 5. execvp: Searches PATH (p), Arguments as a VECTOR (v).
   
    // execvp("ls", argv_list);

    // 6. execve: The raw system call. FULL PATH, VECTOR (v), Explicit ENVIRONMENT (e).
    //existing environment variable is discarded completely and user given variable is used from here on out until the program exits.
    char *envp_list[] = {"VAR1=Execve", "VAR2=Demo", NULL};
    execve("/bin/ls", argv_list, envp_list); // Example using ls with new environment (will only print ls output)


    // --- ERROR CHECKING ---
    // If we reach this point, the exec call failed.
    perror("\n*** EXEC FAILED ***");
    
    // We return a failure status if the new program couldn't be run.
    return EXIT_FAILURE; 
}
