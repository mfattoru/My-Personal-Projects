<!--
Java Server Page che si occupa della visualizzazione dei dettagli di un evento
questa riceve in ingresso l'id dell'evento e un parametro mod (necesario per l'abilitazione
alla modifica),quindi vengono recuperati i dati dal database  e viene costruita una tabella contenente
le info dell'evento.Inoltre viene effettuata anche una geolocalizzazione dell'evento
tramite l'indirizzo dell'evento
-->
<!DOCTYPE html>

<html>
  <head>
    <title>Info Evento</title>
    <%@ page import="java.sql.*"%>
    <%@ page import="javax.sql.*"%>
    <%@ page import="java.util.ArrayList"%>   
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
      //dichiarazione variabili
      String Proprietario="";
      String NomeEvento;
      String Descrizione;
      ArrayList <String> Nome;
      ArrayList <String> Cognome;
      String Luogo;
      String Id;
      String OraInizio;
      String OraFine;
      try{
	if(session.getAttribute("userid")!=null){ //nel caso in cui l'utente sia loggato
	  String Mod=request.getParameter("mod"); //variabile necessaria per controllare se l'utente ha il permesso di modificare l'evento
	  //inizializzazione connessione al database
	  Class.forName("com.mysql.jdbc.Driver");
	  java.sql.Connection con = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123");
	  Id=request.getParameter("Id");
	  Statement st=con.createStatement();
	  //recupero informazioni sull evento
	  ResultSet rs=st.executeQuery("select * from Evento where Id= '"+Id+"'");
	  rs.next();
	  NomeEvento=rs.getString("Nome");
	  Descrizione=rs.getString("Descrizione");
	  Luogo=rs.getString("Luogo");
	  OraInizio=rs.getString("OraInizio");     
	  OraFine=rs.getString("OraFine");
	  rs.close();
	  //recupero partecipanti all'evento
	  rs=st.executeQuery("select P.Nome,P.Cognome,E.Proprietario from PartecipaEvento P RIGHT OUTER JOIN Evento E on E.Id=P.IdEvento where E.Id= '"+Id+"'");
	  Nome=new ArrayList<String>();
	  Cognome=new ArrayList<String>();
	  while(rs.next()){
	    Nome.add(rs.getString(1));
	    Cognome.add(rs.getString(2));
	    Proprietario=rs.getString(3);
	  }
       
	  %>
	  <table border=2  align=center width=400px>  <!--fissa la larghezza della tabella in modo da non farla ridimensionare nel caso in cui siano presenti
							campi troppo lunghi-->
	    <tr>
	      <td colspan="2" >
		<h1 align="center">Nome Evento:<%= NomeEvento %> </h1> <!--stampa nome dell'evento-->
	      </td>
	    </tr>
	    <tr>
	      <td>
		Orario: <%= OraInizio %> - <%= OraFine %> <!--stampa ora dell'evento-->
	      </td>
	      <td>
		<div id="luogo"><%= Luogo %></div> <!--stampa luogo in cui si terrà l'evento-->
	      </td>
	    </tr>
	    <tr>
	      <td colspan="2" >
		<%= Descrizione %> <!--stampa la descrizione dell'evento-->
	      </td>
	      <tr>
		<td colspan=2>
		  <div style="width:400px; height:100px; overflow:scroll;"> <!--stampa la lista di partecipanti all'interno di una cella scrollabile-->
		    Partecipanti:
		    <%
		    for(int i=0;i<Nome.size();i++){
		      if(Cognome.get(i)!=null && Nome.get(i)!=null){
			%>
			<%= Cognome.get(i)%>
			<%= Nome.get(i)%>
			<%
			if(i!=Nome.size()-1){
			  %>
			   ,
			  <%
			}
		      }
		    } 
		    %>
		  </div>
		</td>
	      </tr>
	    </tr>
	    <tr>
	      <td colspan=2>
		<div id="map_canvas" style="width: 400px; height: 300px;"></div>  <!--setta le dimensioni della mappa da inserire nella tabella-->
	      </td>
	    </tr>
	  </table>
	  <center>
	  <br><br>
      
	  <%
	  //se l'utente è loggato e se è il proprietario di quell'evento
	  if(session.getAttribute("userid")!=null && Proprietario.equals((String)session.getAttribute("userid"))){
	    if(Integer.parseInt(Mod)!=75920857){//se l'evento non è ancora terminato.permetti all'utente di poterlo modificare
	      %>
	      <button name="nome" onclick="location.href='../jsp/modificaevento.jsp?Id=<%= Id %>'">Modifica Evento</button> 
	      <%
	    }
	    %><!--permetti all'utente di poter cancellare l'evento-->
	    <button name="nome" onclick="location.href='../jsp/cancellaevento.jsp?Id=<%= Id %>&mod=<%= Mod %>'">Cancella Evento</button>
	    <%
	  }
	  else if(session.getAttribute("userid")!=null){//contrariamente se è loggato ma è solo un partecipante all'evento
	    %><!--permetti di rimuovere la partecipazione all'evento-->
	    <button name="nome" onclick="location.href='../jsp/rimuovipartecipazione.jsp?Id=<%= Id %>'">Rimuovi partecipazione</button>
	    <%
	
	  }
	  %>
	  <button name="eventi" onClick="location.href='../static/calendario.html'">Home Page</button>
	  <%
	}
	else{ //nel caso in cui l'utente non sia loggato effettuo una redirezione sulla pagina di login
	  String redirectURL = "login.jsp";
	  response.sendRedirect(redirectURL);
	}
      }
      catch(Exception e){
	%>
	<p alicg="center">Impossibile visualizzare la pagina,riprovare più tardi</p>
	<%
      }
      %>
      </center>
    </body>
</html>