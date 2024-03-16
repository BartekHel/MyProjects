package pl.polsl.lab.model;

import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.IntStream;
import java.sql.*;

/**
 * Model class. Its task is to handle files input/output, process the data like
 * searching for posts and store them temporarily. It is a singleton class.
 *
 * @author Bartosz Helinski
 * @version 5.0
 */
public class DataManagement {

    private static DataManagement instance;
    private List<String> posts;
    private List<String> history;

    private static Connection connection;
    private static Statement statement;

    /**
     * Establishes a connection to the Derby database upon class initialization.
     * The connection is created using the "jdbc:derby://localhost:1527/Blog" URL
     * with the username "app" and password "app".
     *
     * @throws RuntimeException if there is an error establishing the database connection.
     */
    static {
        try {
            connection = DriverManager.getConnection("jdbc:derby://localhost:1527/Blog", "app", "app");
            statement = connection.createStatement();
        } catch (SQLException exp) {
            throw new RuntimeException("Blad polaczenia z baza danych! ");
        }
    }

    /**
     * Closes the database connection and statement.
     * If the statement or connection is already closed or null, it is ignored.
     *
     * @throws RuntimeException if there is an error closing the database connection or statement.
     */
    public static void closeConnection() {
        try {
            if (statement != null) {
                statement.close();
            }
            if (connection != null) {
                connection.close();
            }
        } catch (Exception exp) {
            throw new RuntimeException("Blad polaczenia z baza danych! ", exp);
        }
    }

    /**
     * Constructs a new instance of {@code DataManagement}.
     * This constructor initializes the database tables (Titles, Contents, Log, and AllLog),
     * creates them if they do not exist, and performs necessary data initialization.
     *
     * @throws RuntimeException if there is an error connecting to the database,
     * executing SQL statements, or handling database metadata.
     */
    public DataManagement() {
        try {
            if (!tableExists(connection, "TITLES")) {
                statement.executeUpdate("CREATE TABLE Titles "
                        + "(id INTEGER PRIMARY KEY NOT NULL, title VARCHAR(50) NOT NULL, "
                        + "posts_num INTEGER NOT NULL)");
                saveTitles();
            }

            if (!tableExists(connection, "CONTENTS")) {
                statement.executeUpdate("CREATE TABLE Contents "
                        + "(id INTEGER PRIMARY KEY NOT NULL, title VARCHAR(50) NOT NULL, "
                        + "content VARCHAR(100), "
                        + "title_id INTEGER NOT NULL, "
                        + "FOREIGN KEY (title_id) REFERENCES Titles(id))");
                saveContents();
            }

            if (!tableExists(connection, "LOG")) {
                statement.executeUpdate("CREATE TABLE Log "
                        + "(id INTEGER PRIMARY KEY NOT NULL, title VARCHAR(50) NOT NULL, "
                        + "action VARCHAR(50))");
            
                if (tableExists(connection, "ALLLOG")) {
                    String deleteAllQuery = "DELETE FROM ALLLOG";
                    statement.executeUpdate(deleteAllQuery);
                }
            } else {
                String deleteQuery = "DELETE FROM LOG";
                statement.executeUpdate(deleteQuery);
                PreparedStatement logStatement = connection.prepareStatement("INSERT INTO Log (id, title, action) VALUES (?, ?, ?)");
                logStatement.setInt(1, 0);
                logStatement.setString(2, "Polaczono z baza danych");
                logStatement.setString(3, "Nazwa - " + "Blog");
                logStatement.executeUpdate();
            }
            
            if (!tableExists(connection, "ALLLOG")) {
                statement.executeUpdate("CREATE TABLE AllLog "
                        + "(id INTEGER PRIMARY KEY NOT NULL, title VARCHAR(50) NOT NULL, "
                        + "action VARCHAR(50))");
            }
        } catch (Exception exp) {
            throw new RuntimeException("Blad polaczenia z baza danych! ", exp);
        }
    }

    /**
     * Checks whether a table with the specified name exists in the database.
     *
     * @param con       the database connection
     * @param tableName the name of the table to check
     * @return {@code true} if the table exists, {@code false} otherwise
     * @throws Exception if there is an error retrieving database metadata
     */
    private static boolean tableExists(Connection con, String tableName) throws Exception {
        DatabaseMetaData metaData = con.getMetaData();
        ResultSet resultSet = metaData.getTables(null, null, tableName, null);
        return resultSet.next();
    }

    /**
     * Metgod to get the singleton object instance of this class.
     *
     * @return Instance of this class object.
     */
    public static synchronized DataManagement getInstance() {
        if (instance == null) {
            instance = new DataManagement();
        }
        return instance;
    }

    /**
     * Method that loads the posts from file to List of String posts. It uses
     * the special algorithm to store title of the posts in odd cells and its
     * contents in even ones. It knows how many posts are there due to the
     * number at the beggining of the file that says how many are there.
     *
     * @throws IncompatibleNumber Exception telling about eighter the problem
     * with the number of the posts or with the file.
     */
    public void loadPosts() throws IncompatibleNumber {
        posts = new ArrayList<>();
        int idx = 1;
        try {
            ResultSet rs = statement.executeQuery("SELECT * FROM Titles");
            while (rs.next()) {
                String title = rs.getString("title");
                posts.add(idx + "." + title);
                idx++;

                int titleId = rs.getInt("id");
                PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM Contents WHERE title_id = ?");
                preparedStatement.setInt(1, titleId);
                ResultSet res = preparedStatement.executeQuery();
                while (res.next()) {
                    posts.add(res.getString("Title") + ": \n" + res.getString("content") + "\n\n");
                }
                res.close();
                preparedStatement.close();
            }
            rs.close();
        } catch (Exception exp) {
            throw new RuntimeException("Blad polaczenia z baza danych! ", exp);
        }
    }

    /**
     * Method used to search for a specific post, requested by the user.
     *
     * @param phrase Title of the post, user is looking for.
     * @return Returns content of the requested post.
     */
    public String search(String phrase) throws IncompatibleNumber {
        try {
            loadPosts();
        } catch (IncompatibleNumber exp) {
            throw new IncompatibleNumber("Blad otwierania pliku: " + exp.getMessage());
        }

        try {
            ResultSet rs = statement.executeQuery("SELECT * FROM Log");
            int id = 0;
            while (rs.next()) {
                int num = rs.getInt("id");
                if (num > id) {
                    id = num;
                }
            }
            id++;

            PreparedStatement logStatement = connection.prepareStatement("INSERT INTO Log (id, title, action) VALUES (?, ?, ?)");

            logStatement.setInt(1, id);
            logStatement.setString(2, "Wyszukano post ");
            logStatement.setString(3, "Tytul - " + phrase);

            logStatement.executeUpdate();
            
            PreparedStatement allLogStatement = connection.prepareStatement("INSERT INTO AllLog (id, title, action) VALUES (?, ?, ?)");

            allLogStatement.setInt(1, id);
            allLogStatement.setString(2, "Wyszukano post ");
            allLogStatement.setString(3, "Tytul - " + phrase);

            allLogStatement.executeUpdate();

        } catch (Exception exp) {
            throw new RuntimeException("Blad polaczenia z baza danych! ", exp);
        }
        
        int idx = 0;
        for (String post : posts) {
            if (idx % 3 == 0) {
                String line = post.substring(post.indexOf('.') + 1).trim();
                if (line.equals(phrase)) {
                    return post + "\n" + posts.get(idx + 1) + posts.get(idx + 2);
                }
            }
            idx++;
        }

        return "Nie znaleziono szukanego posta!";
    }

    /**
     * Method returning table with all posts.
     *
     * @return Return all posts.
     */
    public List<String> getPosts() throws IncompatibleNumber {
        try {
            loadPosts();
        } catch (IncompatibleNumber exp) {
            throw new IncompatibleNumber("Blad otwierania pliku: " + exp.getMessage());
        }

        return posts;
    }

    /**
     * Method returning table with blogs actions history.
     *
     * @return Return blog history.
     */
    public List<String> getHistory() {
        history = new ArrayList<>();
        try {
            ResultSet rs = statement.executeQuery("SELECT * FROM Log");
            while (rs.next()) {
                String title = rs.getString("title");
                String action = rs.getString("action");
                history.add(title + ": " + action + "/n");
            }
            rs.close();
        } catch (Exception exp) {
            throw new RuntimeException("Blad polaczenia z baza danych! ", exp);
        }
        return history;
    }

    /**
     * Method used to add a post by owner of the blog. User has to give the
     * title and content of the posts. Method increments the number of posts at
     * the beggining and then add the given post at the end of the file with the
     * right index.
     *
     * @param title Title of the given post.
     * @param content Content of the given post.
     * @throws IncompatibleNumber Exception telling about eighter the problem
     * with the number of the posts or with the file.
     */
    public void addPost(String title, String content) throws IncompatibleNumber {
        try {
            loadPosts();
        } catch (IncompatibleNumber exp) {
            throw new IncompatibleNumber("Blad otwierania pliku: " + exp.getMessage());
        }

        try {
            ResultSet rs = statement.executeQuery("SELECT * FROM Titles");
            int id = -1;
            int num = 0;
            int count = 1;
            while (rs.next()) {
                int i = rs.getInt("id");
                if (i > num) {
                    num = i;
                }
                if (rs.getString("title").equals(title)) {
                    id = i;
                    count = rs.getInt("posts_num");
                }
            }
            num++;

            if (id == -1) {
                PreparedStatement titlesStatement = connection.prepareStatement("INSERT INTO Titles (id, title, posts_num) VALUES (?, ?, ?)");
                titlesStatement.setInt(1, num);
                titlesStatement.setString(2, title);
                titlesStatement.setInt(3, 1);
                titlesStatement.executeUpdate();

                ResultSet res = statement.executeQuery("SELECT * FROM Contents");
                int idx = 0;
                while (res.next()) {
                    int i = res.getInt("id");
                    if (i > idx) {
                        idx = i;
                    }
                }
                idx++;

                PreparedStatement contentsStatement = connection.prepareStatement("INSERT INTO Contents (id, title, content, title_id) VALUES (?, ?, ?, ?)");

                contentsStatement.setInt(1, idx);
                contentsStatement.setString(2, "Opis");
                contentsStatement.setString(3, content);
                contentsStatement.setInt(4, num);

                contentsStatement.executeUpdate();
            } else {
                PreparedStatement updateStatement = connection.prepareStatement("UPDATE Titles SET posts_num = ? WHERE id = ?");
                count += 1;
                num -= 1;
                if (count > 3) {
                    updateStatement.setInt(1, 3);
                } else {
                    updateStatement.setInt(1, count);
                }
                updateStatement.setInt(2, num);
                updateStatement.executeUpdate();

                ResultSet res = statement.executeQuery("SELECT * FROM Contents");
                int idx = 0;
                while (res.next()) {
                    int i = res.getInt("id");
                    if (i > idx) {
                        idx = i;
                    }
                }
                idx++;

                if (count < 3) {
                    PreparedStatement contentsStatement = connection.prepareStatement("INSERT INTO Contents (id, title, content, title_id) VALUES (?, ?, ?, ?)");
                    contentsStatement.setInt(1, idx);
                    contentsStatement.setString(2, "Recenzja");
                    contentsStatement.setString(3, content);
                    contentsStatement.setInt(4, num);
                    contentsStatement.executeUpdate();
                } else {
                    if (count > 3) {
                        PreparedStatement updatedStatement = connection.prepareStatement("UPDATE Contents SET content = ? WHERE title_id = ? AND title = ?");
                        updatedStatement.setString(1, content);
                        updatedStatement.setInt(2, num);
                        updatedStatement.setString(3, "Inne");
                        updatedStatement.executeUpdate();
                    } else {
                        PreparedStatement contentsStatement = connection.prepareStatement("INSERT INTO Contents (id, title, content, title_id) VALUES (?, ?, ?, ?)");
                        contentsStatement.setInt(1, idx);
                        contentsStatement.setString(2, "Inne");
                        contentsStatement.setString(3, content);
                        contentsStatement.setInt(4, num);
                        contentsStatement.executeUpdate();
                    }
                }
            }

            ResultSet res = statement.executeQuery("SELECT * FROM Log");
            int idd = 0;
            while (res.next()) {
                int numm = res.getInt("id");
                if (numm > idd) {
                    idd = numm;
                }
            }
            idd++;
            
            PreparedStatement logStatement = connection.prepareStatement("INSERT INTO Log (id, title, action) VALUES (?, ?, ?)");
            logStatement.setInt(1, idd);
            if (count > 3)
                logStatement.setString(2, "Zaktualizowano posta ");
            else
                logStatement.setString(2, "Dodano posta ");
            logStatement.setString(3, "Tytul - " + title);
            logStatement.executeUpdate();
            
            PreparedStatement allLogStatement = connection.prepareStatement("INSERT INTO AllLog (id, title, action) VALUES (?, ?, ?)");
            allLogStatement.setInt(1, idd);
            if (count > 3)
                allLogStatement.setString(2, "Zaktualizowano posta ");
            else
                allLogStatement.setString(2, "Dodano posta ");
            allLogStatement.setString(3, "Tytul - " + title);
            allLogStatement.executeUpdate();

        } catch (Exception exp) {
            throw new RuntimeException("Blad polaczenia z baza danych! ", exp);
        }
    }

    /**
     * Method used to delete a requested post. User has to give the index of the
     * post to be deleted. Mehod decrements the nubmer of posts at the beggining
     * and then looks for the appropriate index of the post.
     *
     * @param number Index of the requested post to be deleted.
     * @throws IncompatibleNumber Exception telling about eighter the problem
     * with the number of the posts or with the file.
     */
    public void deletePost(int number) throws IncompatibleNumber {
        try {
            number -= 1;
            statement.executeUpdate("DELETE FROM Contents WHERE title_id = " + number);
            statement.executeUpdate("DELETE FROM Titles WHERE id = " + number);
            
            ResultSet rs = statement.executeQuery("SELECT * FROM Log");
            int id = 0;
            while (rs.next()) {
                int num = rs.getInt("id");
                if (num > id) {
                    id = num;
                }
            }
            id++;
            
            PreparedStatement logStatement = connection.prepareStatement("INSERT INTO Log (id, title, action) VALUES (?, ?, ?)");
            logStatement.setInt(1, id);
            logStatement.setString(2, "Usunieto post ");
            logStatement.setString(3, "Numer - " + number);
            logStatement.executeUpdate();
            
            PreparedStatement allLogStatement = connection.prepareStatement("INSERT INTO AllLog (id, title, action) VALUES (?, ?, ?)");
            allLogStatement.setInt(1, id);
            allLogStatement.setString(2, "Usunieto post ");
            allLogStatement.setString(3, "Numer - " + number);
            allLogStatement.executeUpdate();
        } catch (Exception exp) {
            throw new RuntimeException("Blad polaczenia z baza danych! ", exp);
        }
    }

    /**
     * This method saves titles of video games into the 'Titles' table in the
     * database. Titles are predefined and represent popular video games.
     *
     * @throws RuntimeException if there is an error connecting to the database
     * or executing the SQL statements.
     */
    private void saveTitles() {
        try {
            PreparedStatement addStatement = connection.prepareStatement("INSERT INTO Titles (id, title, posts_num) VALUES (?, ?, ?)");
            ArrayList<String> games = new ArrayList<>();
            games.add("Stardew Valley");
            games.add("Rocket League");
            games.add("Minecraft");
            games.add("Dark Souls III");
            games.add("Overwatch");
            games.add("The Legend of Zelda: Breath of the Wild");
            games.add("The Witcher 3: Wild Hunt");
            games.add("Fortnite");
            games.add("Assassin's Creed Odyssey");
            games.add("League of Legends");
            games.add("Animal Crossing: New Horizons");
            games.add("World of Warcraft");
            games.add("Counter-Strike: Global Offensive");
            games.add("Splatoon 2");
            games.add("Red Dead Redemption 2");
            games.add("Fallout 4");
            games.add("Hollow Knight");
            games.add("NieR: Automata");
            games.add("Star Wars Jedi: Fallen Order");
            games.add("Civilization VI");

            for (int i = 0; i < 20; i++) {
                addStatement.setInt(1, i);
                addStatement.setString(2, games.get(i));
                addStatement.setInt(3, 2);

                addStatement.executeUpdate();
            }

            addStatement.close();
        } catch (Exception exp) {
            throw new RuntimeException("Blad polaczenia z baza danych! ", exp);
        }
    }

    /**
     * This method saves content descriptions and reviews into the 'Contents'
     * table in the database. Content includes descriptions and reviews for the
     * predefined video games.
     *
     * @throws RuntimeException if there is an error connecting to the database
     * or executing the SQL statements.
     */
    private void saveContents() {
        try {
            statement = connection.createStatement();
            PreparedStatement addStatement = connection.prepareStatement("INSERT INTO Contents (id, title, content, title_id) VALUES (?, ?, ?, ?)");
            ArrayList<String> games = new ArrayList<>();
            games.add("Urokliwa gra symulacyjna, w której uprawiasz rośliny i hodujesz zwierzęta.");
            games.add("Polecana ze względu na relaksujący charakter oraz uroczy pikselowy styl grafiki.");
            games.add("Zabawna i dynamiczna gra sportowa, która łączy piłkę nożną z akrobacjami samochodów. ");
            games.add("Polecana ze względu na szybką akcję, proste zasady i możliwość zabawy z przyjaciółmi.");
            games.add("Kultowa gra sandboxowa, w której gracze eksplorują otwarty świat zbudowany z klocków. ");
            games.add("Polecana ze względu na nieograniczone możliwości swobodnej eksploracji.");
            games.add("Brutalna i trudna gra akcji, w ktorej jest wiele trudnych przecuwnikow.");
            games.add("Polecana dla miłośników wyzwań, ceniących głęboką mechanikę walki oraz lore");
            games.add("Dynamiczna strzelanka pierwszoosobowa z zespołową walką, z umiejętnościami. ");
            games.add("Polecana ze względu na intensywne starcia oraz strategiczny charakter rozgrywki.");
            games.add("Wspaniała przygoda akcji-RPG, osadzona w rozległym świecie Hyrule.");
            games.add("Polecana ze względu na piękny otwarty świat i magiczną przygodę.");
            games.add("Epicka gra RPG osadzona w mrocznym świecie fantasy, wcielasz się w Geralta z Rivii.");
            games.add("Polecana ze względu na wciągającą fabułę, rozbudowany system wyborów moralnych.");
            games.add("Popularna gra battle royale, w której 100 graczy walczy o przetrwanie na mapie. ");
            games.add("Polecana ze względu na szybką akcję, kreatywne budowanie i ciągłe aktualizacje.");
            games.add("Akcji-RPG osadzone w starożytnej Grecji, gdzie gracz wciela się w najemnika. ");
            games.add("Polecana ze względu na rozbudowaną historię, otwarty świat do eksploracji.");
            games.add("Popularna gra typu MOBA, gdzie dwie drużyny rywalizują ze sobą, unikalne postacie. ");
            games.add("Polecana ze względu na taktyczną głębię, rywalizację zespołową i stale aktualizacje");
            games.add("Urocza gra symulacyjna, w której gracz przeprowadza się na bezludną wyspę i rozwijając ją. ");
            games.add("Polecana ze względu na relaksujący charakter, kreatywność w projektowaniu.");
            games.add("Legendarna gra MMORPG, której akcja toczy się w fantastycznym świecie Azeroth. ");
            games.add("Polecana ze względu na ogromny świat do eksploracji, epickie rajdy oraz społeczność graczy.");
            games.add("Klasyczna strzelanka pierwszoosobowa, gdzie dwie drużyny - terrorystów i antyterrorystów. ");
            games.add("Polecana ze względu na intensywną akcję, taktyczne podejście i popularność");
            games.add("Barwna strzelanka zespołowa, gdzie gracze kontrolują inklingi, istoty bardzo zdolne.");
            games.add("Polecana ze względu na innowacyjną rozgrywkę, kreatywne mapy i zabawny charakter.");
            games.add("Epicka gra akcji osadzona w dzikim zachodzie, gdzie gracz wciela się w Arthura Morgana. ");
            games.add("Polecana ze względu na głęboką fabułę, realistyczną oprawę wizualną oraz przygody.");
            games.add("Postapokaliptyczna gra RPG, w której gracz przemierza zrujnowany świat po apokalipsie. ");
            games.add("Polecana ze względu na rozbudowany system kraftowania, eksplorację radioaktywnego świata.");
            games.add("Urocza gra platformowa z elementami metroidvanii, gdzie gracz kontroluje małego rycerza. ");
            games.add("Polecana ze względu na precyzyjne sterowanie, bogatą atmosferę i walki z bossami.");
            games.add("Niezwykła gra akcji RPG, osadzona w postapokaliptycznym świecie, gdzie gracz steruje androidami.");
            games.add("Polecana ze względu na fabułę, nietypowe podejście do narracji oraz emocjonalną ścieżkę dźwiękową.");
            games.add("Przygodowa gra akcji osadzona w świecie Gwiezdnych Wojen, gdzie gracz wciela się w młodego Jedi. ");
            games.add("Polecana ze względu na ekscytujące walki świetlnymi mieczami, rozbudowaną fabułę");
            games.add("Strategiczna gra turowa, w której gracz buduje swoją cywilizację od pradziejów do teraz. ");
            games.add("Polecana ze względu na głęboką strategię, rozbudowany system rozwoju.");

            int idx = 0;
            for (int i = 0; i < 40; i++) {
                addStatement.setInt(1, i);
                if (i % 2 == 0) {
                    addStatement.setString(2, "Opis");
                    addStatement.setInt(4, idx);
                } else {
                    addStatement.setString(2, "Recenzja");
                    addStatement.setInt(4, idx);
                    idx++;
                }
                String test = games.get(i);
                addStatement.setString(3, test);

                addStatement.executeUpdate();
            }

            addStatement.close();
        } catch (Exception exp) {
            throw new RuntimeException("Blad polaczenia z baza danych! ", exp);
        }
    }
}
