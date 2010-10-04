public class CellFactory
{
    public static Cell charToCell(char c)
    {
	for(Cell cell : Cell.values())
	    {
		if(cell.getChar() == c)
		    return cell;
	    }
	return Cell.UNKNOWN;
    }
}