import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.RenderingHints;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.MouseInfo;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.geom.AffineTransform;
import java.awt.Font;
import java.util.ArrayList;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.*;
import javax.swing.JComponent;
import javax.swing.JFrame;

// The main class for the game. Configures the basic settings.
public class Window extends JFrame {

	public static int windowWidth = 1895;
	public static int windowHeight = 1055;
	int spawnNum;

	public boolean wHeld = false;
	public boolean aHeld = false;
	public boolean sHeld = false;
	public boolean dHeld = false;
	public boolean mousePress = false;

	public double clickX = MouseInfo.getPointerInfo().getLocation().getX();
	public double clickY = MouseInfo.getPointerInfo().getLocation().getY();

	static final Player player = new Player();

	public static void main(String[] args) {
		new Window();
	}

	// Initializes the window, input listeners, and spawn boxes.
	public Window() {
		GameDrawingPanel gamePanel = new GameDrawingPanel();

		setExtendedState(JFrame.MAXIMIZED_BOTH);
		setUndecorated(true);
		setVisible(true);
		setTitle("Game");

		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		add(gamePanel, BorderLayout.CENTER);

		addMouseListener(new MouseListener() {
			@Override
			public void mouseClicked(MouseEvent arg0) {
				// TODO Auto-generated method stub
			}

			@Override
			public void mouseEntered(MouseEvent e) {
				// TODO Auto-generated method stub
			}

			@Override
			public void mouseExited(MouseEvent e) {
				// TODO Auto-generated method stub
			}

			@Override
			public void mousePressed(MouseEvent e) {
				mousePress = true;
			}

			@Override
			public void mouseReleased(MouseEvent e) {
				// TODO Auto-generated method stub
				mousePress = false;
			}
		});

		addKeyListener(new KeyListener() {

			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == 87) {
					wHeld = true;
				} else if (e.getKeyCode() == 65) {
					aHeld = true;
				} else if (e.getKeyCode() == 83) {
					sHeld = true;
				} else if (e.getKeyCode() == 68) {
					dHeld = true;
				}
			}

			public void keyReleased(KeyEvent e) {
				if (e.getKeyCode() == 87) {
					wHeld = false;
				} else if (e.getKeyCode() == 65) {
					aHeld = false;
				} else if (e.getKeyCode() == 83) {
					sHeld = false;
				} else if (e.getKeyCode() == 68) {
					dHeld = false;
				}
			}

			@Override
			public void keyTyped(KeyEvent arg0) {
				// TODO Auto-generated method stub
			}
		});

		Spawner spawner = new Spawner(gamePanel);
		ScheduledThreadPoolExecutor executor = new ScheduledThreadPoolExecutor(5);

		executor.scheduleAtFixedRate(new RedrawWindow(this), 0L, 20L, TimeUnit.MILLISECONDS);
		executor.scheduleAtFixedRate(spawner, 0L, 1500L, TimeUnit.MILLISECONDS);
		executor.scheduleAtFixedRate(new Shooter(gamePanel), 0L, 250L, TimeUnit.MILLISECONDS);

		this.setVisible(true);
	}

	// Shoots bullets from the player
	class Shooter implements Runnable {
		GameDrawingPanel panel;

		public Shooter(GameDrawingPanel g) {
			panel = g;
		}

		public void run() {
			clickX = MouseInfo.getPointerInfo().getLocation().getX();
			clickY = MouseInfo.getPointerInfo().getLocation().getY();
			panel.Shoot();
		}
	}

	// Spawns enemies at a regular interval, the number of enemies spawned
	// increases with time.
	class Spawner implements Runnable {
		GameDrawingPanel panel;

		public int spawnCount = 1;
		int counter = 0;

		public int getSpawnCount() {
			return spawnCount;
		}

		public Spawner(GameDrawingPanel g) {
			panel = g;
		}

		@Override
		public void run() {
			spawnNum = spawnCount;
			panel.SpawnGobbos(spawnCount);
			counter++;

			if (counter == 10) {
				spawnCount++;
				counter = 0;
			}
		}
	}
	
	// Simple Runnable to call repaint every frame.
	class RedrawWindow implements Runnable {
		Window window;

		public RedrawWindow(Window window) {
			this.window = window;
		}

		public void run() {
			window.repaint();
		}
	}

	// Responsible for spawning enemies and keeps track of bullets
	class GameDrawingPanel extends JComponent {
		public ArrayList<Gobbo> gobbos = new ArrayList<Gobbo>();
		public ArrayList<Bullet> bullets = new ArrayList<Bullet>();

		int width = 1000;
		int height = 800;

		public void SpawnGobbos(int count) {
			for (int i = count; i > 0; i--) {
				int quadrant = (int) (Math.random() * 4);
				int randomStartXPos = 0;
				int randomStartYPos = 0;

				switch (quadrant) {
				case 0:
					randomStartXPos = (int) (Math.random() * 20);
					randomStartYPos = (int) (Math.random() * windowHeight);
					break;

				case 1:
					randomStartXPos = (int) (Math.random() * 20 + (windowWidth - 20));
					randomStartYPos = (int) (Math.random() * windowHeight);
					break;

				case 2:
					randomStartXPos = (int) (Math.random() * windowWidth);
					randomStartYPos = (int) (Math.random() * 20);
					break;

				case 3:
					randomStartXPos = (int) (Math.random() * windowWidth);
					randomStartYPos = (int) (Math.random() * 20 + (windowHeight - 20));
					break;
				}

				gobbos.add(new Gobbo(Gobbo.getpolyXArray(randomStartXPos), Gobbo.getpolyYArray(randomStartYPos),
						randomStartXPos, randomStartYPos, player.getCenterX(), player.getCenterY()));
				Gobbo.gobbos = gobbos;
			}
		}

		// Spawn a bullet at the player's position and fire in the direction of the mouse
		public void Shoot() {
			if (mousePress) {
				if (player.alive) {
					bullets.add(new Bullet(Bullet.getpolyXArray(player.getCenterX() + 12),
							Bullet.getpolyYArray(player.getCenterY() + 12), clickX, clickY));
				}
			}
		}

		// Draw the next frame. Contains most of the game's mechanics as a result.
		public void paint(Graphics g) {
			Timer invulnerability = new Timer();
			Graphics2D graphicSettings = (Graphics2D) g;

			graphicSettings.setColor(Color.decode("#188E0F"));
			graphicSettings.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			graphicSettings.fillRect(0, 0, getWidth(), getHeight());
			graphicSettings.setPaint(Color.BLUE);

			// Controls movement of the player 
			if (aHeld) {
				player.setXVelocity(-3);
			} else if (dHeld) {
				player.setXVelocity(3);
			} else {
				player.setXVelocity(0);
			}

			if (wHeld) {
				player.setYVelocity(3);
			} else if (sHeld) {
				player.setYVelocity(-3);
			} else {
				player.setYVelocity(0);
			}

			if (wHeld && aHeld) {
				player.setXVelocity(-2);
				player.setYVelocity(2);
			} else if (wHeld && dHeld) {
				player.setXVelocity(2);
				player.setYVelocity(2);
			} else if (sHeld && aHeld) {
				player.setXVelocity(-2);
				player.setYVelocity(-2);
			} else if (sHeld && dHeld) {
				player.setXVelocity(2);
				player.setYVelocity(-2);
			}

			// Controls enemies
			for (Gobbo gobbo : gobbos) {
				if (gobbo.alive) {
					gobbo.setTarget(player.getCenterX(), player.getCenterY());
					gobbo.move();

					if (!player.getInvulnerable()) {

						if (gobbo.collision(player.getBounds())) {
							player.decreaseHealth(gobbo.getDamage());
							player.setInvulnerable(true);

							invulnerability.schedule(new TimerTask() {
								public void run() {
									player.setInvulnerable(false);
								}
							}, 2000);
						}
					}

					graphicSettings.setPaint(Color.RED);
					graphicSettings.draw(gobbo);
					graphicSettings.fillPolygon(gobbo);

				} else {
					player.incGold(50);
					gobbos.remove(gobbo);
					gobbo = null;
				}
			}

			// Controls bullets
			for (Bullet bullet : bullets) {

				if (bullet.getPierce() > 0 && bullet.getCenterX() < 2000 && bullet.getCenterX() > 0
						&& bullet.getCenterY() < 1100 && bullet.getCenterY() > 0) {

					bullet.move();

					for (Gobbo gobbo : gobbos) {
						if (gobbo.alive) {
							if (bullet.collision(gobbo.getTrueBounds())) {
								gobbo.decreaseHealth(bullet.getDamage());
								bullet.adjPierce(-1);
							}
						}
						graphicSettings.setPaint(Color.YELLOW);
						graphicSettings.draw(bullet);
						graphicSettings.fillPolygon(bullet);
					}

				} else {
					bullets.remove(bullet);
					bullet = null;
				}
			}

			graphicSettings.setPaint(Color.YELLOW);
			graphicSettings.setFont(new Font("Arial Black", Font.PLAIN, 40));
			String playerGold = Integer.toString(player.getGold());
			graphicSettings.drawString(playerGold, 10, 40);
			graphicSettings.setPaint(Color.BLACK);
			String spawnString = Integer.toString(spawnNum);

			graphicSettings.drawString(spawnString, 1850, 40);
			graphicSettings.translate(player.getCenterX(), player.getCenterY());

			// Controls Player
			if (player.alive) {
				graphicSettings.setPaint(Color.GREEN);
				graphicSettings.setFont(new Font("Arial Black", Font.PLAIN, 20));
				String playerHealth = Integer.toString(player.getHealth());
				graphicSettings.drawString(playerHealth, 0, -10);
				graphicSettings.setPaint(Color.BLUE);

				player.move();

				graphicSettings.draw(player);
				graphicSettings.fillPolygon(player);
			}

		}
	}
}
