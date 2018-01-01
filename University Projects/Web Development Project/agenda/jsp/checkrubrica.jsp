<!--
Java Server Page che si occupa di far selezionare all'utente le persone che intende far partecipare all'evento
Questa pagina quindi,per ogni utente selezionato,andrà ad inviare alla pagina sceltaluogo.jsp tutti gli indirizzi e-mail
dei contatti selezionati.
-->

<!DOCTYPE html>

<html>
  <head>
    <title>Seleziona Partecipanti</title>
    <%@ page import="java.sql.*" %>
    <%@ page import="javax.sql.*" %>
  </head>
  <body>
    <%
      try{
	  String Id;
	  String Nome;
	  String Cognome;
	  String Email;
	  String Anno,Mese,Giorno;
	  int i=0;
	  if(session.getAttribute("userid")!=null){//se l'utente è loggato
	    //recupero parametri dalla request
	    Anno=request.getParameter("Year");
	    Mese=request.getParameter("Month");
	    Giorno=request.getParameter("Day");
	    Id=(String)session.getAttribute("userid");
	    //inizializzazione connessione al database
	    Class.forName("com.mysql.jdbc.Driver");
	    java.sql.Connection con=DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123");
	    Statement st=con.createStatement();
	    //recupero rubrica dell'utente loggato
	    ResultSet rs=st.executeQuery("select * from Rubrica where Proprietario= '"+Id+"'");
	    %>
	    <center>
	    Seleziona Le Persone Da Invitare All'Evento 
	    <form method="post" action="sceltaluogo.jsp">
	    
	      <input type="hidden" name="Year" value="<%=Anno%>" >
	      <input type="hidden" name="Month" value="<%=Mese%>" >
	      <input type="hidden" name="Day" value="<%=Giorno%>" >
	    <%
	    //creazione lista di tutti i contatti presenti nella rubrica dell'utente loggato,con possibilità si selezione tramite checkbox
	    while(rs.next()){
	      i++;
	      Nome=rs.getString("Nome");
	      Cognome=rs.getString("Cognome");
	      Email=rs.getString("Email");
	      %>
		  <input type="checkbox" name="<%=i%>" value="<%=Email%>"><%=Nome%> <%=Cognome%><br>
	      <%
	    }
	    %>
	      <input type="hidden" name="NumMail" value="<%=i%>" > <!--Invio numero di persone a cui si è deciso di inviare un invito per l'evento-->
	    <input type="submit" value="OK">
	    </form>
	    </center>
	    <%
	  }
	  else{ //redirezione nel caso in cui l'utente non sia loggato
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