import java.util.Arrays;
import java.util.Scanner;

public class RemainderReminder {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int width = sc.nextInt();
		int length = sc.nextInt();
		int largeMod = sc.nextInt();
		int midMod = sc.nextInt();
		int smallMod = sc.nextInt();
		int lowerBound = sc.nextInt();
		int upperBound = sc.nextInt();
		
		Integer[] volumes = {0, 0, 0};
		
		for (int i = 1; i <= Math.min(width, length) / 2; i++) {
			int volume = (width - (2 * i)) * (length - (2 * i)) * i;
			if (volume > volumes[0]) {
				volumes[2] = volumes[1];
				volumes[1] = volumes[0];
				volumes[0] = volume;
			} else if (volume > volumes[1]) {
				volumes[2] = volumes[1];
				volumes[1] = volume;
			} else if (volume > volumes[2]) {
				volumes[2] = volume;
			}
		}
		
		int x = largeMod;
		while (x < lowerBound) {
			x += volumes[0];
		}
		
		for (long i = x; i <= upperBound; i += volumes[0]) {
			if (i % volumes[1] == midMod && i % volumes[2] == smallMod) {
				System.out.println(i);
				return;
			}
		}
	}

}
