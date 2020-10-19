USE `tempuraturedata`;
DROP procedure IF EXISTS `LogTempurature`;

DELIMITER $$
USE `tempuraturedata`$$
CREATE PROCEDURE `LogTempurature` (
  t_SensorId      varchar(50),
  t_Tempurature   decimal(6,4)
)
BEGIN
  insert into tempuraturedata.tempurature(
    SensorId,
    Timestamp,
    Tempurature      
  )
  values(
    t_SensorId,
	sysdate(),
    t_Tempurature
  );
END$$

DELIMITER ;