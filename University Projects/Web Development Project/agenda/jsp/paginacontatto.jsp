<!--
Java Server Page che si occupa della visualizzazione dei dati di un contatto
nella propria rubrica.questa riceve in ingresso la mail del contatto per poi recuperare da 
databesa le altre info.dopo aver recuperato tutte le info dell'utente verrà creata
una tabella che ci mostrarà i dati dell'utente.in più è stata aggiunta la geolocalizzazione
dell'utente in base al proprio indirizzo
-->
<!DOCTYPE html>

<html>
    <head>
	<title>Info Contatto</title>
	<%@ page import="java.sql.*"%>
	<%@ page import="javax.sql.*"%>
	<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyBQwyld-63sseJlk5rnF_kPfkKheN3N1jQ&sensor=false">
	</script>
	<script src="../script/creamappa.js" language="JavaScript" type="text/javascript">
	</script>
	<style type="text/css">
	  html { height: 100% }
	  body { height: 100%; margin: 0; padding: 0 }
	  #map_canvas { height: 100% }
	</style>
    </head>

    <body onload="initialize()">
	<%
	    //recupero dari dalla request e dalla session
	    String email = request.getParameter("Email");
	    String IdUtente = (String)session.getAttribute("userid");
	    String indirizzo,telefono,nome,cognome;
	    try{
		if(IdUtente != null){//nel caso in cui l'utente sia loggato
		    //inizializzazione connessione al database
		    Class.forName("com.mysql.jdbc.Driver");
		    java.sql.Connection con = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123");
		    Statement st = con.createStatement();
		    //recuper informazioni dal database sul contatto 
		    ResultSet rs = st.executeQuery("select * from Rubrica where Proprietario = '"+IdUtente+"' and Email = '"+email+"'");
		    rs.next();
		    indirizzo = rs.getString("Indirizzo");
		    email = rs.getString("Email");
		    telefono = rs.getString("Telefono");
		    nome=rs.getString("Nome");
		    cognome=rs.getString("Cognome");
	%>
		    <center>
			<table border="2" width=400px> <!--larghezza 400 in modo da non rendere la tabella ingrandibile in base
							alla lunghezza dei campi-->
			    <tr>
				<td colspan="2"> <h2> contatto:<%= nome+" "+cognome%> </h2> </td> <!--stampa nome e cognome del contatto-->
			    </tr>

			    <tr>
				<td> Email: <%= email%> </td> <!--stampa email del contatto-->
				<td> telefono: <%= telefono%> </td> <!--stampa numero di telefono del contatto-->
			    </tr>

			    <tr>
				 <td colspan=2> <!--il campo occupa due celle della riga-->
				  Indirizzo:<div id="luogo"><%=indirizzo%></div>  <!--stampa indirizzo del contatto-->
				 </td>
			    </tr>
			    <tr>
			      <td colspan="2">
				<div id="map_canvas" style="width: 400px; height: 300px;"></div>  <!--dimensione della mappa da visualizzare-->
			      </td>
			    </tr>
			</table>
			<button name="modifica" onClick="location.href='modificacontatto.jsp?Email=<%=email%>'">Modifica Contatto</button>
			<button name="cancella" onClick="location.href='cancellacontatto.jsp?Email=<%=email%>'">Elimina Contatto</button>
			<button name="rubrica" onClick="location.href='rubrica.jsp'">Rubrica</button>
		    </center>
	<%
		}
		else{  //redirezione alla pagina di login inl caso in cui l'utente non sia loggato
		    String redirectURL = "login.jsp";
		    response.sendRedirect(redirectURL);
		}
	    }
	    catch(Exception e){
	%>
		<p align="center">errore durante l'interrogazione al database</p>
	<%
	    }
	%>
    </body>

</html>