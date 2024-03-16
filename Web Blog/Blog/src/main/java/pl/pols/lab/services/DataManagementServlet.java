package pl.pols.lab.services;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import pl.polsl.lab.model.DataManagement;
import pl.polsl.lab.model.IncompatibleNumber;

/**
 * Servlet responsible for handling requests to display a list of posts managed by DataManagement.
 * The servlet responds to GET requests and retrieves the list of posts from the DataManagement instance,
 * displaying them in an HTML table.
 * Servlet implementation class for the "/datamanagement" URL pattern.
 * @author Bartosz Helinski
 * @version 1.1
 */

@WebServlet(name = "DataManagementServlet", urlPatterns = {"/datamanagement"})
public class DataManagementServlet extends HttpServlet {

    private DataManagement management;
    
    /**
     * Initializes the servlet by obtaining an instance of DataManagement for data handling.
     */

    @Override
    public void init() {
        management = DataManagement.getInstance();
    }
    
    /**
     * Handles GET requests by displaying a list of posts managed by DataManagement in an HTML table.
     *
     * @param request  The HttpServletRequest object representing the client's GET request.
     * @param response The HttpServletResponse object representing the servlet's response.
     * @throws ServletException If a servlet-specific problem occurs.
     * @throws IOException If an I/O error occurs while processing the request.
     */

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            List<String> posts = management.getPosts();
            out.println("<html>");
            out.println("<head><title>Posty</title></head>");
            out.println("<body>");
            out.println("<h1>Lista postów:</h1>");

            out.println("<table border='1'>");
            out.println("<tr><th>Posty</th></tr>");

            for (String post : posts) {
                post = post.replaceAll("\n", "<br>");

                out.println("<tr><td>" + post + "</td></tr>");
            }

            out.println("</table>");

            out.println("</body>");
            out.println("</html>");
        } catch (Exception exp) {
            PrintWriter out = response.getWriter();
            out.println("<h1>Blad podczas wyswietlania postow!</h1>");
            out.println("<p>" + exp.getMessage() + "</p>");
            exp.printStackTrace(new PrintWriter(out));
        }
    }
}
