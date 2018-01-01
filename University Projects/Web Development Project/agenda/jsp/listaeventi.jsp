<!--
Java Server Page che si occupa della creazione di una lista di eventi per un determinato giorno.
La Pagina accetta in ingresso una data e crea una tabella che elenca tutti gli eventi che l'utente ha creato
o a cui l'utente sta partecipando
-->
<!DOCTYPE html>

  <html>
	<head>
	  <title>Lista Eventi</title>
	  <%@ page import = "java.sql.*"%>
	  <%@ page import = "javax.sql.*"%>
	  <%@ page import = "java.util.*"%>
	</head>
	<body>
	  <%
	try{
	  if(session.getAttribute("userid")!=null){
	    //dichiarazione variabili
	    String Giorno;
	    String Mese;
	    String Anno;
	    String Data;
	    String Nome;
	    String Id;
	    String OraInizio;
	    String OraFine;
	    String Utente;
	    Calendar DataSelezionata = Calendar.getInstance();
	    Calendar DataAttuale = Calendar.getInstance();
	    Calendar cal = new GregorianCalendar();
	    int mod=74910653;
	    //recupero data corrente
	    int CurDay = cal.get(Calendar.DAY_OF_MONTH);
	    int CurMonth = cal.get(Calendar.MONTH);
	    int CurYear = cal.get(Calendar.YEAR);
	    //recupero data del giorno selezionato
	    Giorno=request.getParameter("day");     
	    Mese=request.getParameter("month");
	    Anno=request.getParameter("year");
	    DataSelezionata.set(Integer.parseInt(Anno), Integer.parseInt(Mese)-1, Integer.parseInt(Giorno));
	    DataAttuale.set(CurYear, CurMonth, CurDay);
	    Data=Anno+'-'+Mese+'-'+Giorno;
	    //confronto data corrente con data selezionata
	    if(!DataSelezionata.after(DataAttuale) && !DataSelezionata.equals(DataAttuale)){
	      mod=75920857;  //nega la modifica dell evento nella pagina dell'evento nel caso in cui l'evento sia stato gia terminato
	    }
	    Utente=(String)session.getAttribute("userid");
	    //inizializzazione connessione al database
	    Class.forName("com.mysql.jdbc.Driver");
	    java.sql.Connection con=DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123");
	    Statement st=con.createStatement();
	    //recupero di tutti gli eventi nella data selezionata
	    ResultSet rs=st.executeQuery("select distinct E.Nome,E.OraInizio,E.OraFine,E.Id from Evento E LEFT OUTER JOIN PartecipaEvento P on E.Id=P.IdEvento where E.Data= '"+Data+"' and (P.IdUtente= '"+Utente+"' or E.Proprietario= '"+Utente+"')");
	 %>
	 <center>
	 <table width=600 height=40 border=2 aling=center>
	    <tr>
	      <td>  <center>  <b> Nome Evento </b>  </center></td>
	      <td>  <center>  <b> Ora Inizio  </b>  </center></td>
	      <td>  <center>  <b> Ora Fine    </b>  </center></td>
	    </tr>
	 <%
	    while(rs.next()){
	      Nome=rs.getString(1);
	      OraInizio=rs.getString(2);
	      OraFine=rs.getString(3);
	      Id=rs.getString(4);

	 %>
	      <tr>
	        <td>  <center> <a href="paginaevento.jsp?Id=<%= Id %>&mod=<%=mod%>" >  <%= Nome %> </a>   </center></td>
		<td>  <center> <%= OraInizio %>                                              </center></td> 
		<td>  <center> <%= OraFine %>                                                </center></td>
	      </tr>
	
	 <%
		
	    }
	 %>
	 </table>
	 <br>
	 <%
	 //nega l'aggiunta di un evento nel caso in cui l'evento sia gia terminato
	 if(DataSelezionata.after(DataAttuale) || DataSelezionata.equals(DataAttuale)){
	 %>
	  <button name="nome" onclick="location.href='checkrubrica.jsp?Year=<%=Anno%>&Month=<%=Mese%>&Day=<%=Giorno%>'">Aggiungi Evento</button>
	 <%
	 }
	 %>
	 <button name="nome" onclick="location.href='../static/calendario.html'">Home Page</button>
	 </center>
	 <%
      }
      else{//redirezione nel caso in cui l'utente non sia loggato
	  String redirectURL = "login.jsp";
	  response.sendRedirect(redirectURL);
      }
    }catch(Exception e){
    %>
      <p align="center">errore durante la cancellazione </p>
    <%
    }
    %>
  </body>
</html>
