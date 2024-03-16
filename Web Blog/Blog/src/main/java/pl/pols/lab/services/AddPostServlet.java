package pl.pols.lab.services;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

import pl.polsl.lab.model.DataManagement;
import pl.polsl.lab.model.IncompatibleNumber;

/**
 * Servlet responsible for handling requests to add a new blog post.
 * The servlet responds to both GET and POST requests for adding a new post with the provided title and content.
 * Servlet implementation class for the "/addpost" URL pattern.
 * @author Bartosz Helinski
 * @version 1.1
 */
        
@WebServlet(name = "AddPostServlet", urlPatterns = {"/addpost"})
public class AddPostServlet extends HttpServlet {

    private DataManagement management;
    
    /**
     * Initializes the servlet by obtaining an instance of DataManagement for data handling.
     */
    
    @Override
    public void init() {
        management = DataManagement.getInstance();
    }
    
    /**
     * Processes both GET and POST requests related to adding a new blog post with the provided title and content.
     * @param request  The HttpServletRequest object representing the client's request.
     * @param response The HttpServletResponse object representing the servlet's response.
     * @throws ServletException If a servlet-specific problem occurs.
     * @throws IOException If an I/O error occurs while processing the request.
     */
    
    protected void processRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");

        String ar1 = request.getParameter("arg1");
        String ar2 = request.getParameter("arg2");
        
        ar2 = ar2.replace('0', '\n');

        try {
            management.addPost(ar1, ar2);
            PrintWriter out = response.getWriter();
            out.println("Post dodany");
        } catch (Exception exp) {
            PrintWriter out = response.getWriter();
            out.println("<h1>Blad podczas dodawania posta!</h1>");
            out.println("<p>" + exp.getMessage() + "</p>");
            exp.printStackTrace(new PrintWriter(out));
        }
    }
    
    /**
     * Handles GET requests by delegating to the common request processing method.
     * @param request  The HttpServletRequest object representing the client's GET request.
     * @param response The HttpServletResponse object representing the servlet's response.
     * @throws ServletException If a servlet-specific problem occurs.
     * @throws IOException If an I/O error occurs while processing the request.
     */
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }
    
    /**
     * Handles POST requests by delegating to the common request processing method.
     * @param request  The HttpServletRequest object representing the client's POST request.
     * @param response The HttpServletResponse object representing the servlet's response.
     * @throws ServletException If a servlet-specific problem occurs.
     * @throws IOException      If an I/O error occurs while processing the request.
     */

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }
    
    /**
     * Returns information about the servlet.
     * @return A string containing servlet information.
     */

    @Override
    public String getServletInfo() {
        return "Informacje";
    }
}