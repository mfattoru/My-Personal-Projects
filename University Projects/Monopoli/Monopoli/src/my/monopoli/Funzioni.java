/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package my.monopoli;

import java.awt.CardLayout;
import java.awt.Toolkit;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import javax.swing.JOptionPane;
import javax.swing.JComboBox;
import net.proteanit.sql.DbUtils;

/**
 *
 * @author Michele
 */
public class Funzioni {
    
    public static void InizializzaComboBox(JComboBox Box,String sql) throws Exception{
        Statement stmt=null;
        ResultSet rset=null;
        Box.removeAllItems();
        Box.addItem(" ");
        try{
            stmt=my.monopoli.MonopoliUI.conn.createStatement();
            rset=stmt.executeQuery(sql);
            while(rset.next()){
                Box.addItem(rset.getString(1));
            }
        }
        catch(SQLException e){
            throw e;
        }
        finally{
            try{
                if(rset!=null){
                    rset.close();
                }
                if(stmt!=null){
                    stmt.close();
                }
            } 
            catch(SQLException f){
                JOptionPane.showMessageDialog(null, "Errore Chiusura ResultSet: " +f.getMessage(),"ResultSet Error",JOptionPane.ERROR_MESSAGE);   
            }
        }
    }
    
    public static void InizializzaTabellone() throws Exception{
        Statement stmt=null;
        ResultSet rset=null;
        Statement stmt2=null;
        String sql;
        try{
            stmt=my.monopoli.MonopoliUI.conn.createStatement();
            stmt2=my.monopoli.MonopoliUI.conn.createStatement();
            rset=stmt.executeQuery("SELECT * FROM CONTRATTI ORDER BY ID_CONTRATTO");
            while(rset.next()){
                if(rset.getString("EDIFICABILE").equals("Y")){
                    sql="INSERT INTO TABELLONE(PARTITA,CASELLA,ORDINE,N_CASE,ALBERGO) VALUES ("+my.monopoli.MonopoliUI.ID+","+rset.getString("ID_CONTRATTO") +",0,0,'N')";
                    //stmt2=my.monopoli.MonopoliUI.conn.createStatement();
                    stmt2.executeUpdate(sql);
                }
                else{
                    sql="INSERT INTO TABELLONE(PARTITA,CASELLA,ORDINE) VALUES ("+my.monopoli.MonopoliUI.ID+","+rset.getString("ID_CONTRATTO") + ",0)";
                    //stmt=my.monopoli.MonopoliUI.conn.createStatement();
                    stmt2.executeUpdate(sql);
                }
               
            }
            JOptionPane.showMessageDialog(null,"Inizializzazione Tabellone Completata","Inizializzazione Completata",JOptionPane.INFORMATION_MESSAGE);   
        }
        catch(SQLException e){
            throw e;
        }
        finally{
            try{
                if(rset!=null){
                    rset.close();
                }
                if(stmt!=null){
                    stmt.close();
                }
            } 
            catch(SQLException f){
                JOptionPane.showMessageDialog(null,f.getMessage(),"Statement Error",JOptionPane.ERROR_MESSAGE);   
            }
        }
    }

    
    
    
    
    
}
