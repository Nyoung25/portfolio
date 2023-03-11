package tree;

import java.util.Collection;

/**
 * This class represents a non-empty search tree. An instance of this class
 * should contain:
 * <ul>
 * <li>A key
 * <li>A value (that the key maps to)
 * <li>A reference to a left Tree that contains key:value pairs such that the
 * keys in the left Tree are less than the key stored in this tree node.
 * <li>A reference to a right Tree that contains key:value pairs such that the
 * keys in the right Tree are greater than the key stored in this tree node.
 * </ul>
 *  
 */
 public class NonEmptyTree<K extends Comparable<K>, V> implements Tree<K, V> {

	private K key;
	private V value;
	private Tree<K, V> left, right;
	

	/**
	 * Only constructor we need.
	 * @param key
	 * @param value
	 * @param left
	 * @param right
	 */
	public NonEmptyTree(K key, V value, Tree<K,V> left, Tree<K,V> right) {
		this.key = key;
		this.value = value;
		this.left = left;
		this.right = right;
	}

	public V search(K key) {
		int comparison = key.compareTo(this.key);
		
		if (comparison < 0) {
			return left.search(key);
		} else if (comparison > 0) {
			return right.search(key);
		} else {
			return value;
		}
	}
	
	public NonEmptyTree<K, V> insert(K key, V value) {
		int comparison = key.compareTo(this.key);
		
		if (comparison < 0) {
			left = left.insert(key, value);
		} else if (comparison > 0) {
			right = right.insert(key, value);
		} else {
			this.value = value;
		}
		return this;
	}
	
	public Tree<K, V> delete(K key) {
		int comparison = key.compareTo(this.key);
		boolean rightExists = true;
		
		if (comparison < 0) {
			left = left.delete(key);
		} else if (comparison > 0) {
			right = right.delete(key);
		} else {
			/* this block executes when the passed key is equal to this object's key.
			 * It checks whether the left and right subtrees are empty using the
			 * min and max functions, then returns based on its findings.
			 */
			try {
				right.min();
			} catch (TreeIsEmptyException e) {
				rightExists = false;
			} finally {
				try {
					K lMax = left.max();
					if (rightExists) {
						//when left and right both exist - uses end return statement
						this.key = lMax;
						this.value = left.search(lMax);
						left.delete(lMax);
					} else {
						//when only left exists
						return left;
					}
				} catch (TreeIsEmptyException e) {
					if (rightExists) {
						//when only right exists
						return right;
					} else {
 						//when neither left nor right exist (therefore it is a leaf)
						return EmptyTree.getInstance();
					}
				}
			}
		}
		/* only returns this when either one of the first two if statements are true, 
		 * or if left and right both referenced the EmptyTree instance.
		 */
		return this;
	}

	public K max() {
		try {
			return right.max();
		} catch (TreeIsEmptyException e) {
			return key;
		}
	}

	public K min() {
		try {
			return left.min();
		} catch (TreeIsEmptyException e) {
			return key;
		}
	}

	public int size() {
		return 1 + left.size() + right.size();
	}

	public void addKeysToCollection(Collection<K> c) {
		left.addKeysToCollection(c);
		c.add(key);
		right.addKeysToCollection(c);
	}
	
	public Tree<K,V> subTree(K fromKey, K toKey) {
		
		if (key.compareTo(fromKey) >= 0 && key.compareTo(toKey) <= 0) {
			 return new NonEmptyTree<K, V>(key, value,
					 left.subTree(fromKey, toKey), right.subTree(fromKey, toKey));
			 
		} else if (key.compareTo(fromKey) < 0) {
			return right.subTree(fromKey, toKey);
		} else { 
			// key here must be greater than toKey (assuming fromKey is less than toKey)
			return left.subTree(fromKey, toKey);
		} 
	}
	
	public int height() {
		return Math.max(left.height(), right.height()) + 1;
	}
	
	public void inorderTraversal(TraversalTask<K,V> p) {
		left.inorderTraversal(p);
		p.performTask(key, value);
		right.inorderTraversal(p);
	}
	
	public void rightRootLeftTraversal(TraversalTask<K,V> p) {
		right.rightRootLeftTraversal(p);
		p.performTask(key, value);
		left.rightRootLeftTraversal(p);
	}	
}