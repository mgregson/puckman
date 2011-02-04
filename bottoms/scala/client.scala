import java.util._

class Board (width: Int, elements: String) {

      def puckman = rawToPoint((1+elements.indexOf('C')+elements.indexOf('@')))

      def rawToPoint(raw : Int) = (raw/width,raw%width)

      def at(x : Int, y: Int) = elements.charAt(x*width+y)

      override def toString() : String = {
            (0 to width-1).foldLeft("")((i,s) => i+elements.substring(s,s+width)+"\n")
      }

}

object Board {
      def readBoard() {
	  val scanner = new Scanner(System.in)
	  val w = scanner.nextInt()
	  val str = ""
	  new Board(w,str)
      }
}

val board = new Board(2,"a@cd")
println("Lols "+board.puckman)
val board2 = Board.readBoard()