import java.io.InputStream;

public class WorldParser
{
    public void parse(InputStream stream, int width, World world)
    {
	int x = 0;
	int y = 0;
	char in;
	do
	    {
		in = (char)stream.read();
		world.setCell(x,y,CellFactory.charToCell(in));
		if(x >= width)
		    {
			y++;
			x = 0;
		    }
	    }
	while(in != '\n');
	world.updateComplete();
    }
}