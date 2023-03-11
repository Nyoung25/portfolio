import java.awt.Polygon;
import java.awt.Rectangle;

// The player's character
class Player extends Polygon {

	public boolean alive = true;

	public static int[] polyXArray = { 0, 25, 25, 0 };
	public static int[] polyYArray = { 25, 25, 0, 0 };

	private int xVelocity = 0;
	private int yVelocity = 0;

	private int health = 25;

	private int width = 25;
	private int height = 25;

	private int gold = 0;

	int wWidth = Window.windowWidth;
	int wHeight = Window.windowHeight;

	private boolean invulnerable = false;

	private double centerX = wWidth / 2, centerY = wHeight / 2;

	private int uLeftXPos = super.xpoints[0];
	private int uLeftYPos = super.ypoints[0];

	Rectangle boundingBox = new Rectangle((int) centerX, (int) centerY + 25, height, width);

	public Player() {
		super(polyXArray, polyYArray, 4);
	}

	public void move() {
		uLeftXPos = super.xpoints[0];
		uLeftYPos = super.ypoints[0];
		
		// Prevents the player from leaving the window
		if (xVelocity + centerX > 1895) {
			centerX = 1895;
		}
		
		if (xVelocity + centerX < 0) {
			centerX = 0;
		} else {
			this.centerX += xVelocity;
		}
		
		if (yVelocity + centerY > 1055) {
			this.centerY = 1055;
		}
		
		if (yVelocity + centerY < 0) {
			this.centerY = 5;
		} else {
			this.centerY -= yVelocity;
		}
		
		if (health <= 0) {
			alive = false;
		}

		boundingBox.setLocation((int) centerX, (int) centerY);
	}

	public Rectangle getBounds() {
		return boundingBox;
	}

	public boolean getInvulnerable() {
		return invulnerable;
	}

	public void setInvulnerable(boolean invul) {
		invulnerable = invul;
	}

	public int getGold() {
		return gold;
	}

	public void setGold(int gold) {
		this.gold = gold;
	}

	public void incGold(int amount) {
		gold += amount;
	}

	public double getWidth() {
		return width;
	}

	public double getHeight() {
		return height;
	}

	public double getULeftX() {
		return uLeftXPos;
	}

	public double getULeftY() {
		return uLeftYPos;
	}

	public double getCenterX() {
		return centerX;
	}

	public double getCenterY() {
		return centerY;
	}

	public void setCenterX(double centX) {
		centerX = centX;
	}

	public void setCenterY(double centY) {
		centerY = centY;
	}

	public void adjCenterX(double amount) {
		centerX += amount;
	}

	public void adjCenterY(double amount) {
		centerY += amount;
	}

	public int getXVelocity() {
		return xVelocity;
	}

	public int getYVelocity() {
		return yVelocity;
	}

	public void setXVelocity(int xVel) {
		xVelocity = xVel;
	}

	public void setYVelocity(int yVel) {
		yVelocity = yVel;
	}

	public void adjXVelocity(int amount) {
		xVelocity += amount;
	}

	public void adjYVelocity(int amount) {
		yVelocity += amount;
	}

	public int getHealth() {
		return health;
	}

	public void setHealth(int hP) {
		health = hP;
	}

	public void decreaseHealth(int amount) {
		health -= amount;
	}

	public void setAlive(boolean alv) {
		alive = alv;
	}

}
