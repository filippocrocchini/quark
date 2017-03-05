import java.util.ArrayList;
import java.util.List;

import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.GameObject;

public class CrappyGame{
	List<GameObject> gameObjects;
	
	public CrappyGame() {
		gameObjects = new ArrayList<GameObject>();
	}

	public void setup() {
		gameObjects.add(Engine.getGameObjectManager().createGameObject(TestGameObject.class));
	}
}
