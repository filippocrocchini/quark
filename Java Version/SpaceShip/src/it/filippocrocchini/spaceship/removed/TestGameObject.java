import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.GameObject;

public class TestGameObject extends GameObject{
	
	public void setup() {		
		addComponent(Engine.getGameObjectManager().createComponent(this, FPSLoggerComponent.class));
		addComponent(Engine.getGameObjectManager().createComponent(this, RectangleComponent.class));
	}

	public void onLoad() {		
	}

	public void cleanup() {		
	}


}
