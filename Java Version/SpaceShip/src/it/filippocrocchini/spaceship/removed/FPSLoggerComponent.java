import it.filippocrocchini.engine.common.component.Updatable;

public class FPSLoggerComponent extends Updatable{
	private double frameTime = 0;
	
	public void update(double delta) {		
		if(frameTime < 1000) {
			frameTime += delta;
		} else {
			System.out.println("Update: " + 1000/delta+ " FPS");
			frameTime -= 1000.0;
		}
	}
}
