import java.awt.Polygon;
import java.util.ArrayList;
import java.util.concurrent.TimeUnit;
import java.awt.Rectangle;
import java.awt.geom.Rectangle2D;

// The basic enemy

public class Gobbo extends Polygon {

	public boolean alive = true;

	public static int[] polyXArray = { 0, 25, 25, 0 };
	public static int[] polyYArray = { 25, 25, 0, 0 };

	public static int[] sPolyXArray = { 0, 25, 25, 0 };
	public static int[] sPolyYArray = { 25, 25, 0, 0 };

	private double xVelocity = 0;
	private double yVelocity = 0;

	private int health = 10;

	private int damage = 5;

	private int width = 25;
	private int height = 25;

	private int wWidth = 1000;
	private int wHeight = 800;

	private double targetX;
	private double targetY;

	Rectangle bounds = new Rectangle(this.getBounds());

	static ArrayList<Gobbo> gobbos = new ArrayList<Gobbo>();

	int uLeftXPos = super.xpoints[0];
	int uLeftYPos = super.ypoints[0];

	private double centerX = uLeftXPos, centerY = uLeftYPos;

	public Gobbo(int[] polyXArray, int[] polyYArray, int randomStartXPos, int randomStartYPos, double tarX,
			double tarY) {

		super(polyXArray, polyYArray, 4);
		this.uLeftXPos = randomStartXPos;
		this.uLeftYPos = randomStartYPos;
		this.targetX = tarX;
		this.targetY = tarY;

	}

	public void move() {

		if (health <= 0) {

			alive = false;

		}

		centerX = uLeftXPos;
		centerY = uLeftYPos - 25;

		uLeftXPos = super.xpoints[0];
		uLeftYPos = super.ypoints[0];

		bounds.setLocation(uLeftXPos - 2, uLeftYPos - 25);

		double deltaX = this.targetX - this.centerX;
		double deltaY = this.targetY - this.centerY;

		double angle = Math.atan2(deltaY, deltaX);

		double xVel = 3 * Math.cos(angle);
		double yVel = 3 * Math.sin(angle);
		for (int i = 0; i < xpoints.length; i++) {

			super.xpoints[i] += xVel;
		}
		for (int i = 0; i < ypoints.length; i++) {
			super.ypoints[i] += yVel;
		}

	}

	public Boolean collision(Rectangle r) {

		if (bounds.intersects(r)) {
			return true;
		} else {
			return false;
		}

	}

	public static int[] getpolyXArray(int randomStartXPos) {

		int[] tempPolyXArray = (int[]) sPolyXArray.clone();
		
		for (int i = 0; i < tempPolyXArray.length; i++) {
			tempPolyXArray[i] += randomStartXPos;
		}

		return tempPolyXArray;
	}

	public static int[] getpolyYArray(int randomStartYPos) {
		int[] tempPolyYArray = (int[]) sPolyYArray.clone();

		for (int i = 0; i < tempPolyYArray.length; i++) {
			tempPolyYArray[i] += randomStartYPos;
		}
		
		return tempPolyYArray;
	}

	public Rectangle getTrueBounds() {
		return bounds;
	}

	public double getCenterX() {
		return centerX;
	}

	public double getCenterY() {
		return centerY;
	}

	public void setCenterX(float centX) {
		this.centerX = centX;
	}

	public void setCenterY(float centY) {
		this.centerY = centY;
	}

	public void adjCenterX(float amount) {
		this.centerX += amount;
	}

	public void adjCenterY(float amount) {
		this.centerY += amount;
	}

	public int getDamage() {
		return damage;
	}

	public void setDamage(int dmg) {
		this.damage = dmg;
	}

	public void adjDamage(int amount) {
		this.damage += amount;
	}

	public int getHealth() {
		return health;
	}

	public void setHealth(int hP) {
		this.health = hP;
	}

	public void decreaseHealth(int amount) {
		this.health -= amount;
	}

	public void setTarget(double targetX, double targetY) {
		this.targetX = targetX;
		this.targetY = targetY;
	}
}
