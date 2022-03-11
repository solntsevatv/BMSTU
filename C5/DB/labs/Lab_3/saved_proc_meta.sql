CREATE OR REPLACE PROCEDURE metadata_lab_3(tname VARCHAR)
AS 
$$
DECLARE
    elem RECORD;
BEGIN
	RAISE NOTICE 'Table:  %', tname;
    FOR elem IN
        SELECT column_name, data_type
        FROM information_schema.columns
        WHERE table_name = tname
    LOOP
            RAISE NOTICE '%, %', elem.column_name, elem.data_type;
    END LOOP;
END;
$$ LANGUAGE plpgsql;