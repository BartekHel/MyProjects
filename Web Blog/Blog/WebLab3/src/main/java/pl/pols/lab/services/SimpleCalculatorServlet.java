package pl.pols.lab.services;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import pl.polsl.lab.model.Calculator;

@WebServlet(name = "SimpleCalculatorServlet", urlPatterns = {"/simplecalculator"})
public class SimpleCalculatorServlet extends HttpServlet {

    private Calculator calculator;
    
    @Override
    public void init() {
        calculator = new Calculator();
    }
    
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        
        Cookie c = null;
        Cookie[] ck  = request.getCookies();
        if(ck != null) {
            for(Cookie cookie : ck) {
                if("calculationsCount".equals(cookie.getName())){
                    c = cookie;
                }
            }
        }

        int count = c == null ? 1 : Integer.parseInt(c.getValue()) + 1;
        
        String arg1 = request.getParameter("arg1");
        String arg2 = request.getParameter("arg2");
        
        if(arg1 == null || arg2 == null || arg1.length() == 0 || arg2.length() == 0){
            response.sendError(response.SC_BAD_REQUEST, "Wymagane są dwa parametry!!!");
        } else {
            try{
                PrintWriter out = response.getWriter();                
                out.println("[" + count +"] " + arg1 + " + " + arg2 + " = " + Double.toString(calculator.operations(Double.parseDouble(arg1), Double.parseDouble(arg2))));
            } catch(Exception ex) {
                response.sendError(response.SC_BAD_REQUEST, "Wymagane są liczby!!!");
            }
        }
        response.addCookie(new Cookie("calculationsCount", Integer.toString(count)));
        
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
