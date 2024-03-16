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
 * Servlet responsible for handling requests related to the history of the blog.
 * The servlet responds to both GET and POST requests, displaying the blog's history in HTML format.
 * Servlet implementation class for the "/history" URL pattern.
 * @author Bartosz Helinski
 * @version 1.1
 */
        
@WebServlet(name = "HistoryServlet", urlPatterns = {"/history"})
public class HistoryServlet extends HttpServlet {

    private DataManagement management;
    
    /**
     * Initializes the servlet by obtaining an instance of DataManagement for data handling.
     */
    
    @Override
    public void init() {
        management = DataManagement.getInstance();
    }
    
    /**
     * Processes both GET and POST requests related to blog history and generates an HTML response.
     * @param request  The HttpServletRequest object representing the client's request.
     * @param response The HttpServletResponse object representing the servlet's response.
     * @throws ServletException If a servlet-specific problem occurs.
     * @throws IOException If an I/O error occurs while processing the request.
     */
    
    protected void processRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");

        try (PrintWriter out = response.getWriter()) {
            List<String> history = management.getHistory();
            out.println("<html>");
            out.println("<body>");
            out.println("<h1>Historia bloga (database):</h1>");
            
            int idx = history.size();
            for (int i = history.size() - 1; i >=0; i--) {
                String line = history.get(i).replaceAll("/n", "<br>");
                out.println("[" + idx + "] " + line);
                idx--;
            }

            out.println("</body>");
            out.println("</html>");
        } catch (Exception exp) {
            PrintWriter out = response.getWriter();
            out.println("<h1>Blad podczas wyswietlania historii!</h1>");
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