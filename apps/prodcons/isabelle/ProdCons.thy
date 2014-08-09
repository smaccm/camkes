(*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 *)

(* THIS FILE IS AUTOMATICALLY GENERATED. YOUR EDITS WILL BE OVERWRITTEN. *)
theory ProdCons
imports Types Abbreviations Connector
begin









(* Connections *)
datatype channel


    = cb

    | pb


(* Component instances *)
datatype inst


    = b

    | c

    | p


    

    




    (* Buffer's interfaces *)
    datatype Buffer_channel
    
    
        = Buffer_outgoing
    
        | Buffer_incoming
    

    
    

    
    
        definition
            Recv_Buffer_outgoing :: "(Buffer_channel \<Rightarrow> channel) \<Rightarrow>
            
                
                (channel, 'cs) comp \<Rightarrow>
                
                    ('cs local_state \<Rightarrow> 
    
        nat
    
) \<Rightarrow>
                
                
            
            (channel, 'cs) comp"
        where
            
            "Recv_Buffer_outgoing ch0'
            
                
                Buffer_outgoing_get
                
                    get_return\<^isub>P
                
                
            
            \<equiv>
            
                
                
                
                
                
                (Response (\<lambda>s1' s2'. case q_data s1' of Call s3' s4' \<Rightarrow> (if s3' = 0 then {(
                
                    s2'
                
                , \<lparr>a_channel = ch0' Buffer_outgoing, a_data = Void\<rparr>)} else {}) | _ \<Rightarrow> {}) ;;
                Buffer_outgoing_get ;;
                
                Request (\<lambda>s5'. {\<lparr>q_channel = ch0' Buffer_outgoing, q_data = Return (
                
                    
    
        Number
    
 (get_return\<^isub>P s5') #
                
                
                [])\<rparr>}) discard)
            
            "
    
        definition
            Recv_Buffer_incoming :: "(Buffer_channel \<Rightarrow> channel) \<Rightarrow>
            
                
                    ('cs local_state \<Rightarrow>
                    
                        
    
        nat
    
 \<Rightarrow>
                    
                    'cs local_state) \<Rightarrow>
                
                (channel, 'cs) comp \<Rightarrow>
                
                
            
            (channel, 'cs) comp"
        where
            
            "Recv_Buffer_incoming ch6'
            
                
                    put\<^isub>E
                
                Buffer_incoming_put
                
                
            
            \<equiv>
            
                
                
                
                
                
                (Response (\<lambda>s7' s8'. case q_data s7' of Call s9' s10' \<Rightarrow> (if s9' = 0 then {(
                
                    put\<^isub>E s8'
                    
                        
                        (case s10' ! 0 of 
    
        Number
    
 s11' \<Rightarrow> s11')
                    
                
                , \<lparr>a_channel = ch6' Buffer_incoming, a_data = Void\<rparr>)} else {}) | _ \<Rightarrow> {}) ;;
                Buffer_incoming_put ;;
                
                Request (\<lambda>s12'. {\<lparr>q_channel = ch6' Buffer_incoming, q_data = Return (
                
                
                [])\<rparr>}) discard)
            
            "
    

    
    

    
    

    
    



    (* Consumer's interfaces *)
    datatype Consumer_channel
    
    
        = Consumer_b
    

    
    
        
            definition
                Call_Consumer_b_get :: "(Consumer_channel \<Rightarrow> channel) \<Rightarrow>
                
                
                
                    ('cs local_state \<Rightarrow> 
    
        nat
    

                
                
                
                    
                    \<Rightarrow> 'cs local_state) \<Rightarrow>
                
                (channel, 'cs) comp"
            where
                
                "Call_Consumer_b_get ch13'
                
                
                    embed
                
                
                \<equiv> Request (\<lambda>s14'. {\<lparr>q_channel = ch13' Consumer_b, q_data = Call 0 (
                
                [])\<rparr>}) discard ;;
                
                
                
                Response (\<lambda>s15' s16'. case q_data s15' of Return s17' \<Rightarrow>
                
                    {(embed s16'
                    
                        
                        (case hd s17' of 
    
        Number
    
 s18' \<Rightarrow> s18')
                    
                    
                
                , \<lparr>a_channel = ch13' Consumer_b, a_data = Void\<rparr>)} | _ \<Rightarrow> {})"
        
    

    
    

    
    

    
    

    
    



    (* Producer's interfaces *)
    datatype Producer_channel
    
    
        = Producer_b
    

    
    
        
            definition
                Call_Producer_b_put :: "(Producer_channel \<Rightarrow> channel) \<Rightarrow>
                
                    ('cs local_state \<Rightarrow> 
    
        nat
    
) \<Rightarrow>
                
                
                
                
                
                (channel, 'cs) comp"
            where
                
                "Call_Producer_b_put ch19'
                
                    value\<^isub>P
                
                
                
                \<equiv> Request (\<lambda>s20'. {\<lparr>q_channel = ch19' Producer_b, q_data = Call 0 (
                
                    
    
        Number
    
 (value\<^isub>P s20') #
                
                [])\<rparr>}) discard ;;
                
                
                
                Response (\<lambda>s21' s22'. case q_data s21' of Return s23' \<Rightarrow>
                
                    {(s22'
                
                , \<lparr>a_channel = ch19' Producer_b, a_data = Void\<rparr>)} | _ \<Rightarrow> {})"
        
    

    
    

    
    

    
    

    
    



(* Component instantiations *)

    

    

    
        definition
            Recv_b_outgoing :: "
            
                
                (channel, 'cs) comp \<Rightarrow>
                
                    ('cs local_state \<Rightarrow> 
    
        nat
    
) \<Rightarrow>
                
                
            
            (channel, 'cs) comp"
        where
            "Recv_b_outgoing \<equiv>
                
                Recv_Buffer_outgoing (\<lambda>s24'. case s24' of
                
                
                    
                    
                         Buffer_outgoing \<Rightarrow> cb
                    
                
                    
                    
                        | Buffer_incoming \<Rightarrow> pb
                    
                
                )"
    
        definition
            Recv_b_incoming :: "
            
                
                    ('cs local_state \<Rightarrow>
                    
                        
    
        nat
    
 \<Rightarrow>
                    
                    'cs local_state) \<Rightarrow>
                
                (channel, 'cs) comp \<Rightarrow>
                
                
            
            (channel, 'cs) comp"
        where
            "Recv_b_incoming \<equiv>
                
                Recv_Buffer_incoming (\<lambda>s25'. case s25' of
                
                
                    
                    
                         Buffer_outgoing \<Rightarrow> cb
                    
                
                    
                    
                        | Buffer_incoming \<Rightarrow> pb
                    
                
                )"
    

    

    

    


    

    
        
            definition
                Call_c_b_get :: "
                
                
                
                    ('cs local_state \<Rightarrow> 
    
        nat
    

                
                
                
                    
                    \<Rightarrow> 'cs local_state) \<Rightarrow>
                
                (channel, 'cs) comp"
            where
                "Call_c_b_get \<equiv>
                    
                    Call_Consumer_b_get (\<lambda>s26'. case s26' of
                    
                    
                        
                             Consumer_b \<Rightarrow> cb
                        
                        
                    
                        
                        
                    
                    )"
        
    

    

    

    

    


    

    
        
            definition
                Call_p_b_put :: "
                
                    ('cs local_state \<Rightarrow> 
    
        nat
    
) \<Rightarrow>
                
                
                
                
                
                (channel, 'cs) comp"
            where
                "Call_p_b_put \<equiv>
                    
                    Call_Producer_b_put (\<lambda>s27'. case s27' of
                    
                    
                        
                        
                    
                        
                             Producer_b \<Rightarrow> pb
                        
                        
                    
                    )"
        
    

    

    

    

    



locale system_state =
    fixes init_component_state :: 'cs
    fixes trusted :: "(inst, ((channel, 'cs) comp \<times> 'cs local_state)) map"
begin


    
    definition
        Buffer_untrusted :: "(Buffer_channel \<Rightarrow> channel) \<Rightarrow> (channel, 'cs) comp"
    where
        
        "Buffer_untrusted ch28' \<equiv>
            LOOP (
                UserStep
                
                    \<squnion> ArbitraryRequest (ch28' Buffer_outgoing)
                    \<squnion> ArbitraryResponse (ch28' Buffer_outgoing)
                
                    \<squnion> ArbitraryRequest (ch28' Buffer_incoming)
                    \<squnion> ArbitraryResponse (ch28' Buffer_incoming)
                
            )"

    
    definition
        Consumer_untrusted :: "(Consumer_channel \<Rightarrow> channel) \<Rightarrow> (channel, 'cs) comp"
    where
        
        "Consumer_untrusted ch29' \<equiv>
            LOOP (
                UserStep
                
                    \<squnion> ArbitraryRequest (ch29' Consumer_b)
                    \<squnion> ArbitraryResponse (ch29' Consumer_b)
                
            )"

    
    definition
        Producer_untrusted :: "(Producer_channel \<Rightarrow> channel) \<Rightarrow> (channel, 'cs) comp"
    where
        
        "Producer_untrusted ch30' \<equiv>
            LOOP (
                UserStep
                
                    \<squnion> ArbitraryRequest (ch30' Producer_b)
                    \<squnion> ArbitraryResponse (ch30' Producer_b)
                
            )"








(* Component instantiations *)

    

    definition
        b_untrusted :: "(channel, 'cs) comp"
    where
        
        "b_untrusted \<equiv> Buffer_untrusted (\<lambda>s31'. case s31' of
        
        
            
            
                 Buffer_outgoing \<Rightarrow> cb
            
        
            
            
                | Buffer_incoming \<Rightarrow> pb
            
        
        )"


    

    definition
        c_untrusted :: "(channel, 'cs) comp"
    where
        
        "c_untrusted \<equiv> Consumer_untrusted (\<lambda>s32'. case s32' of
        
        
            
                 Consumer_b \<Rightarrow> cb
            
            
        
            
            
        
        )"


    

    definition
        p_untrusted :: "(channel, 'cs) comp"
    where
        
        "p_untrusted \<equiv> Producer_untrusted (\<lambda>s33'. case s33' of
        
        
            
            
        
            
                 Producer_b \<Rightarrow> pb
            
            
        
        )"









(* Global initial state *)

definition
    gs\<^isub>0 :: "(inst, channel, 'cs) global_state"
where
    
    
    "gs\<^isub>0 p34' \<equiv> case trusted p34' of Some s35' \<Rightarrow> Some s35' | _ \<Rightarrow> (case p34' of
    
    
         b \<Rightarrow> Some (b_untrusted, Component init_component_state)
    
        | c \<Rightarrow> Some (c_untrusted, Component init_component_state)
    
        | p \<Rightarrow> Some (p_untrusted, Component init_component_state)
    
    
        
    
        
    
    )"

end

end
