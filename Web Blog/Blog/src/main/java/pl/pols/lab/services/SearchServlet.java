package pl.pols.lab.services;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

import pl.polsl.lab.model.DataManagement;
import pl.polsl.lab.model.IncompatibleNumber;

/**
 * Servlet responsible for handling search requests and displaying search
 * results. The servlet responds to both GET and POST requests for searching a
 * blog post based on the provided search argument. It also tracks and displays
 * the search history using cookies. Servlet implementation class for the
 * "/simplesearch" URL pattern.
 * @author Bartosz Helinski
 * @version 1.1
 */
@WebServlet(name = "SearchServlet", urlPatterns = {"/simplesearch"})
public class SearchServlet extends HttpServlet {

    private DataManagement management;

    /**
     * Initializes the servlet by obtaining an instance of DataManagement for
     * data handling.
     */
    @Override
    public void init() {
        management = DataManagement.getInstance();
    }

    /**
     * Processes both GET and POST requests related to searching for a blog post
     * and displays the search results. It also tracks and displays the search
     * history using cookies.
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

        Cookie searchCountCookie = null;
        Cookie otherCountCookie = null;
        List<String> lastSearches = new ArrayList<>();

        Cookie[] cookies = request.getCookies();
        if (cookies != null) {
            for (Cookie cookie : cookies) {
                String cookieName = cookie.getName();
                if (cookieName.startsWith("lastSearch")) {
                    lastSearches.add(cookie.getValue());
                } else if ("searchCount".equals(cookie.getName())) {
                    searchCountCookie = cookie;
                } else if ("otherCount".equals(cookie.getName())) {
                    otherCountCookie = cookie;
                }
            }
        }

        int searchCount = (searchCountCookie == null) ? 0 : Integer.parseInt(searchCountCookie.getValue());
        int otherCount = (otherCountCookie == null) ? 0 : Integer.parseInt(otherCountCookie.getValue());

        String arg = request.getParameter("arg1");
        String post = "";

        try {
            post = management.search(arg);
            PrintWriter out = response.getWriter();
            out.println("<h1>Szukany post:</h1>");
            out.println("<ul>");
            post = post.replaceAll("\n", "<br>");

            if (post.equals("Nie znaleziono szukanego posta!")) {
                searchCount++;
                out.println("[" + searchCount + "] " + post);
            } else {
                otherCount++;
                out.println("[" + otherCount + "] " + post);

                if (!lastSearches.isEmpty()) {
                    out.println("<br><br><h1 style='text-align: center;'>Ostatnio szukane posty (cookies):</h1>");

                    out.println("<div style='margin: auto; width: 50%;'>");
                    out.println("<table border='1' style='width: 100%; margin: auto; text-align: center;'>");
                    out.println("<tr><th>Indeks</th><th>Tytuł</th></tr>");

                    int idx = lastSearches.size();
                    for (int i = lastSearches.size() - 1; i >= 0; i--) {
                        out.println("<tr><td>" + "[" + idx + "]</td><td>" + lastSearches.get(i) + "</td></tr>");
                        idx--;
                    }

                    out.println("</table>");
                    out.println("</div>");
                }

                for (int i = 0; i < lastSearches.size(); i++) {
                    response.addCookie(new Cookie("lastSearch" + i, lastSearches.get(i)));
                }

                StringBuilder truncatedArg = new StringBuilder();
                for (int i = 0; i < arg.length(); i++) {
                    char currentChar = arg.charAt(i);

                    if (Character.isWhitespace(currentChar)) {
                        break;
                    }

                    if (Character.isLetter(currentChar)) {
                        truncatedArg.append(currentChar);
                    }
                }
                response.addCookie(new Cookie("lastSearch" + (otherCount - 1), truncatedArg.toString()));
            }
        } catch (Exception exp) {
            PrintWriter out = response.getWriter();
            out.println("<h1>Blad podczas wyszukiwania posta!</h1>");
            out.println("<p>" + exp.getMessage() + "</p>");
            exp.printStackTrace(new PrintWriter(out));
        }

        response.addCookie(new Cookie("searchCount", Integer.toString(searchCount)));
        response.addCookie(new Cookie("otherCount", Integer.toString(otherCount)));
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
