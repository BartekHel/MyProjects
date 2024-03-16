import pl.polsl.lab.model.DataManagement;
import pl.polsl.lab.model.IncompatibleNumber;

import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;

/**
 * Class of unit tests.
 * Tests all methods used in model class to determine whether they function correctly.
 * @author Bartosz Helinski
 * @version 4.0
 */

public class PostsTest {
    
    private DataManagement management;
    
    /**
     * This test checks the loading files and posts method in the model class if they are being loaded correctly.
     */
    
    @Test
    public void testLoad() {
        try {
            management.loadPosts();
            fail("No such database! ");
        } 
        catch (Exception exp) {
        }
    }
    
    /**
     * This test checks the searching for a post method in the model class if it functions correctly.
     */
    
    @Test
    public void testSearch() {
        try {
            management.loadPosts();
            String tmp = management.search("Minecraft");
            assertEquals(tmp, "Post not found!");
        } 
        catch (Exception exp) {
        }
        
        try {
            management.loadPosts();
            String tmp = management.search(".");
        } 
        catch (Exception exp) {
        }
        
        try {
            management.loadPosts();
            String tmp = management.search(" ");
            fail("Search failed!");
        } 
        catch (Exception exp) {
        }

    }
    
    /**
     * This test checks the adding a post method in the model class if it adds the post correctly.
     */
    
    @Test
    public void testAdd() {
        try {
            management.addPost("B", "b");
            String tmp = management.search("B");
            fail("Search failed!");
        } 
        catch (Exception exp) {
        } 
        
        try {
            management.addPost(".", ".");
            String tmp = management.search(".");
            fail("Search failed!");
        } 
        catch (Exception exp) {
        } 
        
        try {
            management.addPost("B", "cc");
            fail("Adding post failed! ");
        } 
        catch (Exception exp) {
        } 
        
        try {
            management.addPost(" ", " 0 0x");
            String tmp = management.search(" ");
            assertNotEquals(tmp, "Post not found!");
        } 
        catch (Exception exp) {
        } 
    }
    
    /**
     * This test checks the deleting a post method in the model class if it deletes the post correctly.
     */
    
    @Test
    public void testDelete() {
        try {
            management.addPost("X", "x\nx\nx");
            management.deletePost(4);
            String tmp = management.search("X");
            assertNotEquals(tmp, "Post not found!");
        } 
        catch (Exception exp) {
        } 
        
        try {
            management.deletePost(100);
            fail("Deleting post failed! ");
        } 
        catch (Exception exp) {
        } 
        
        try {
            management.deletePost(-1);
            fail("Deleting post failed! ");
        } 
        catch (Exception exp) {
        } 
    }
}