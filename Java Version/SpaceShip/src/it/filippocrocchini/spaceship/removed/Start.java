import it.filippocrocchini.engine.common.Engine;

public class Start {
	public static void main(String[] args) {
		CrappyGame game = new CrappyGame();
		Engine.create("Game", 720, 480, true);
		game.setup();
		Engine.start();
	}
}
