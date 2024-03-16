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
 * Servlet responsible for opening data base at the beggining.
 * The servlet responds to both GET and POST requests for connecting to a base.
 * Servlet implementation class for the"/database" URL pattern.
 * @author Bartosz Helinski
 * @version 1.1
 */
@WebServlet(name = "DataBaseServlet", urlPatterns = {"/database"})
public class DataBaseServlet extends HttpServlet {

    private DataManagement management;

    /**
     * Initializes the servlet by obtaining an instance of DataManagement for
     * data handling.
     */
    @Override
    public void init() throws ServletException {
        try {
            management = DataManagement.getInstance();
        } catch (Exception exp) {
            log("Blad inicjalizacji: " + exp.getMessage(), exp);
            getServletContext().setAttribute("initError", exp);
        }
    }

    /**
     * Processes both GET and POST requests related to connecting to a database
     * and displays errors taht occured.
     *
     * @param request The HttpServletRequest object representing the client's
     * request.
     * @param response The HttpServletResponse object representing the servlet's
     * response.
     * @throws ServletException If a servlet-specific problem occurs.
     * @throws IOException If an I/O error occurs while processing the request.
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        try {
            management.loadPosts();
        } catch (Exception exp) {
            PrintWriter out = response.getWriter();
            out.println("<h1>Błąd! </h1>");
            out.println("<br><br><br><br><br><br>");
            out.println("<p>" + exp.getMessage() + "</p>");
            exp.printStackTrace(new PrintWriter(out));
        }
    }
    
    /**
     * Handles GET requests by delegating to the common request processing
     * method.
     *
     * @param request The HttpServletRequest object representing the client's
     * GET request.
     * @param response The HttpServletResponse object representing the servlet's
     * response.
     * @throws ServletException If a servlet-specific problem occurs.
     * @throws IOException If an I/O error occurs while processing the request.
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles POST requests by delegating to the common request processing
     * method.
     *
     * @param request The HttpServletRequest object representing the client's
     * POST request.
     * @param response The HttpServletResponse object representing the servlet's
     * response.
     * @throws ServletException If a servlet-specific problem occurs.
     * @throws IOException If an I/O error occurs while processing the request.
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns information about the servlet.
     *
     * @return A string containing servlet information.
     */
    @Override
    public String getServletInfo() {
        return "Informacje";
    }
}
