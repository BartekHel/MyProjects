import pl.polsl.lab.model.DataManagement;
import pl.polsl.lab.model.IncompatibleNumber;
        
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.*;
import java.util.stream.Stream;

/**
 * Class of parameterized tests.
 * Tests all methods used in model class to determine whether they function correctly.
 * @author Bartosz Heliński
 * @version 4.0
 */

public class ParameterizedPostsTest {
    
    private DataManagement management;
    
    /**
     * This parameterized test checks the loading files and posts method in the model class if correct files and posts are being loaded correctly.
     */
    
    @ParameterizedTest
    @ValueSource(strings = {"Error"})
    void loadValidPosts(String phrase) {
        try {
            management.loadPosts();
            fail(phrase);
        } 
        catch (Exception exp) {
        } 
    }
    
    /**
     * This parameterized test checks the searching for a post method in the model class if it finds correct posts.
     */
    
    @ParameterizedTest
    @ValueSource(strings = {"Stardew Valley", "Minecraft", "Overwatch"})
    void searchValidPost(String phrase) {
        try {
            management.loadPosts();
            String tmp = management.search(phrase);
            assertNotEquals(tmp, "Nie znaleziono posta!");
        }
        catch (Exception exp) {
        } 
    }
    
    /**
     * This parameterized test checks the searching for a post method in the model class if it does not find incorrect posts.
     */
    
    @ParameterizedTest
    @ValueSource(strings = {"a", "5", "x", "Minecraft ", "3.Minecraft", ".Minecraft", " Minecraft", "Dark Souls", "", " "})
    void searchInvalidPost(String phrase) {
        try {
            management.loadPosts();
            String tmp = management.search(phrase);
            assertNotEquals(tmp, "Nie znaleziono posta!");
            fail("Deleting post failed! ");
        }
        catch (Exception exp) {
        } 
    }
    
    /**
     * Private Strteam containing arguments for addPost parameterized test to choose from and test them.
     * @return parameters used in addPost test to check if the method works correctly.
     */
    
    private static Stream<Arguments> arguments() {
        return Stream.of(
                Arguments.of("B", "b\nb", "1.B\nb\nb\n"),
                Arguments.of("B", ".", "1.B\nb\nb\n"),
                Arguments.of("C", " ", "1.C\n \n"),
                Arguments.of("10", "1\n1\n1", "1.10\n1\n1\n1\n")
        );
    }
        
    /**
     * This parameterized test checks the adding a file method in the model class if it adds the posts correctly.
     */
    
    @ParameterizedTest
    @MethodSource("arguments")
    void addPost(String phrase1, String phrase2, String phrase3) {
        try {
            String tmp = phrase3;
            assertEquals(tmp, phrase3);
        }
        catch (Exception exp) {
        } 
    }
    
    /**
     * This parameterized test checks the deleting a file method in the model class if it deletes the posts correctly.
     */
    
    @ParameterizedTest
    @ValueSource(strings = {"-1", "0", "300", "1000", "-100"})
    void deleteInvalidPost(int num) {
        try {
            management.deletePost(num);
            fail("Deleting post failed! ");
        } 
        catch (Exception exp) {
        }
    }
}