<!--
Java Server Page che si occupa della modifica di un contatto da parte dell'utente.
alla prima apertura della pagina viene presentato un form precompilato contenente i
dati dell'evento,qui l'utente potrà modificare i campi della form e successivamente 
confermare la modifica dei dati.questi campi saranno quindi recuperati dalla stessa pagina 
che si occuperà della modifica dei dati nel database
-->
<!DOCTYPE html>

<html>
  <head>
    <title>Modifica Contatto</title>
    <%@ page import="java.sql.*" %>
    <%@ page import="javax.sql.*" %>
  </head>
  <body>
    <%
      try{
	  //dichiarazioni variabili
	  String Id;
	  String Nome;
	  String Cognome;
	  String Email;
	  String Indirizzo;
	  String Telefono;
	  if(session.getAttribute("userid")!=null){ //se 'utente è loggato
	    //recupero dati dalla request e dalla session
	    Id=(String)session.getAttribute("userid");
	    Email=request.getParameter("Email");
	    //inizializzo la connessione al database
	    Class.forName("com.mysql.jdbc.Driver");
	    java.sql.Connection con=DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123");
	    Statement st=con.createStatement();
	    //recupero tutti i dati appartenenti al contatto della rubrica precedentemente selezionato
	    ResultSet rs=st.executeQuery("select * from Rubrica where Proprietario= '"+Id+"' and Email='"+Email+"'");
	    if(rs.next()){ //se il contatto esiste mi recupero i suoi dati
	      Nome=rs.getString("Nome");
	      Cognome=rs.getString("Cognome");
	      Indirizzo=rs.getString("Indirizzo");
	      Telefono=rs.getString("Telefono");
	      //successivamente mostro all'utente una form con i campi precompilati,contenenti i dati dell'utente selezionato.
	      //tramite questa form l'utente potrà modificare i dati dell'utente.
	      %>
		<form name="modificaContatto" id="modificaContatto" align="center" method="POST" action="aggiornacontatto.jsp">
		  <input type="hidden" name="OldEmail" value="<%=Email%>" >
		  <!--Nome (caratteri, lettere accentate apostrofo e un solo spazio fra le parole)-->
		  Nome:<input type="text" name="Nome" value="<%=Nome%>" required pattern="^([a-zA-Z\xE0\xE8\xE9\xF9\xF2\xEC\x27]\s?)+$" title="caratteri, lettere accentate apostrofo e un solo spazio fra le parole"><br> 
		  <!--Cognome (caratteri, lettere accentate apostrofo e un solo spazio fra le parole)-->
		  Cognome:<input type="text" name="Cognome"  value="<%=Cognome%>" required pattern="^([a-zA-Z\xE0\xE8\xE9\xF9\xF2\xEC\x27]\s?)+$" title="caratteri, lettere accentate apostrofo e un solo spazio fra le parole"><br>
		  Email:<input type="text" name="Email" value= "<%=Email%>" required pattern="^[a-zA-Z0-9._%-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$"><br>
		  <!--Indirizzo,(caratteri,numeri,virgola, lettere accentate ,apostrofo e un solo spazio fra le parole) -->
		  Indirizzo:<input type="text" name="Indirizzo" value="<%=Indirizzo%>" required pattern="^([a-zA-Z0-9\ \xE0\xE8\xE9\xF9\xF2\xEC\x27,])+$" title="(caratteri,numeri,virgola, lettere accentate ,apostrofo e un solo spazio fra le parole)"><br>
		  <!--telefono composto da 10 cifre-->
		  Telefono:<input type="text" name="Telefono"  value="<%=Telefono%>" required pattern="^\d{10}$" title="numero composto da 10 cifre"><br><br>
		  <input type="submit" value="Modifica Contatto">
		  <input type="reset" value="Cancella campi">
		</form>
	      <%
	    }
	  }
	else{ //redirezione nel caso in cui l'utente non è loggato
	  String redirectURL = "login.jsp";
	  response.sendRedirect(redirectURL);
	}
      }
      catch(Exception e){
	%>
	  <p align="center">errore durante l'inserimento</p>
	<%
      }
    %>
  </body>
</html>