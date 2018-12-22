
import java.io.IOException;


public interface Bigram<T> {
                public abstract void readFile(String fileName)throws IOException;
		public abstract int numGrams();
		public abstract int numOfGrams(T p1 , T p2);
                @Override
                public String toString();
}
