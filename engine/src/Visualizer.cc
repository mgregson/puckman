#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <iostream>
#include <sys/select.h>

#include "Visualizer.h"

#include "defines.h"

Visualizer::Visualizer(char* cmd)
{

  int writepipe[2];
  int waitpipe[2];


  if(pipe(writepipe))
    {
      std::cerr << "Failed to create write pipe!"
		<< std::endl;
      perror("Visualizer.cc");
      exit(2);
    }
  if(pipe(waitpipe))
    {
      std::cerr << "Failed to create write pipe!"
		<< std::endl;
      perror("Visualizer.cc");
      exit(2);
    }

  if(pid = fork())
    {
      if(pid < 0)
	{
	  std::cerr << "Unable to fork!"
		    << std::endl;
	  perror("Visualizer.cc");
	  exit(3);
	}

      close(writepipe[0]);
      kidout = fdopen(writepipe[1], "w");
      if(!kidout)
	{
	  std::cerr << "Can't open kidout fd!"
		    << std::endl;
	  perror("Visualizer.cc");
	  exit(7);
	}
      
      setvbuf(kidout, NULL, _IONBF, 0);
      int foo = 1;
      write(waitpipe[1], &foo, 1);
      close(waitpipe[0]);
      close(waitpipe[1]);


    }
  else
    {
      close(writepipe[1]);

      dup2(writepipe[0], 0);

      int foo;
      read(waitpipe[0], &foo, 1);
      close(waitpipe[0]);
      close(waitpipe[1]);

      execv(cmd, NULL);
      exit(4);
    }
}

Visualizer::~Visualizer()
{

}

void Visualizer::send_world(World* world)
{
  int outbs = 0;
  int d = 0;
  int e = 0;
  int tries = 0;
  fprintf(kidout, "%d\n", world->getWidth());
  for(int i = 0; i < world->getWidth(); i++)
    {
      write(1, &world->grid[i*world->getWidth()], world->getWidth());
      std::cout << std::endl;
    }

  while(outbs < world->getWidth()*world->getWidth())
    {
      d = write(fileno(kidout),
		&world->grid[outbs],
		world->getWidth()*world->getWidth()-outbs);
      if(d < 0)
	e++;
      else
	outbs += d;
      std::cerr << "Wrote " << d << " bytes." << std::endl;
	  
      if(e >= 3 || ++tries > 10)
	{
	  std::cerr << "Error writing to "
		    << "child process.  "
		    << "Is only visualizer...."
		    << std::endl;
	  break;
	}
    }
  write(fileno(kidout), "\n", 1);
}
