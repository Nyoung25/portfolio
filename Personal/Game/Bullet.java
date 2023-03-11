import java.awt.Polygon;
import java.awt.Rectangle;

// The projectiles that the player shoots
public class Bullet extends Polygon {

	boolean alive = true;

	public static int[] sPolyXArray = { 0, 0, 5, 5 };
	public static int[] sPolyYArray = { 0, 5, 5, 0 };

	private int width = 25;
	private int height = 25;

	private int pierce = 1;

	private int damage = 5;

	private int wWidth = 1000;
	private int wHeight = 800;

	private double moveAngle;

	private int uLeftXPos;
	private int uLeftYPos;

	private double xVel;
	private double yVel;

	Rectangle bounds = new Rectangle(this.getBounds());
	private double centerX = uLeftXPos, centerY = uLeftYPos - 2;

	public Bullet(int[] polyXArray, int[] polyYArray, double targetX, double targetY) {
		super(polyXArray, polyYArray, 4);

		uLeftXPos = super.xpoints[0];
		uLeftYPos = super.ypoints[0];

		centerX = uLeftXPos;
		centerY = uLeftYPos - 2;

		double deltaX = targetX - this.centerX;
		double deltaY = targetY - this.centerY;

		double angle = Math.atan2(deltaY, deltaX);

		xVel = 10 * Math.cos(angle);
		yVel = 10 * Math.sin(angle);

	}

	public void move() {
		uLeftXPos = super.xpoints[0];
		uLeftYPos = super.ypoints[0];

		bounds.setLocation(uLeftXPos, uLeftYPos);

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

	public static int[] getpolyXArray(double randomStartXPos) {
		int[] tempPolyXArray = (int[]) sPolyXArray.clone();

		for (int i = 0; i < tempPolyXArray.length; i++) {
			tempPolyXArray[i] += randomStartXPos;
		}

		return tempPolyXArray;
	}

	public static int[] getpolyYArray(double randomStartYPos) {
		int[] tempPolyYArray = (int[]) sPolyYArray.clone();

		for (int i = 0; i < tempPolyYArray.length; i++) {
			tempPolyYArray[i] += randomStartYPos;
		}
		
		return tempPolyYArray;
	}

	public double getCenterX() {
		return centerX;
	}

	public double getCenterY() {
		return centerY;
	}

	public void setCenterX(double centX) {
		this.centerX = centX;
	}

	public void setCenterY(double centY) {
		this.centerY = centY;
	}

	public void adjCenterX(double amount) {
		this.centerX += amount;
	}

	public void adjCenterY(double amount) {
		this.centerY += amount;
	}

	public double getXVelocity() {
		return xVel;
	}

	public double getYVelocity() {
		return yVel;
	}

	public void setXVelocity(int xVel) {
		this.xVel = xVel;
	}

	public void setYVelocity(int yVel) {
		this.yVel = yVel;
	}

	public void adjXVelocity(int amount) {
		this.xVel += amount;
	}

	public void adjYVelocity(int amount) {
		this.yVel += amount;
	}

	public int getDamage() {
		return damage;
	}

	public void setDamage(int damage) {
		this.damage = damage;
	}

	public int getPierce() {
		return pierce;
	}

	public void adjPierce(int amount) {
		pierce += amount;
	}

	public void setAlive(boolean alv) {
		alive = alv;
	}
}
