
options(mc.cores = 4)

#setwd("/home/sfischme/Documents/acerta/pilots/ROS")
setwd("/Users/gretacutulenco/Documents/greta_dev/pilots/GPS-driving-reporting/")

## load Acerta
Sys.setenv(R_TRACES_DIR="../traces")
q <- getwd()
setwd("../../../tstat/site/Rserver")
setwd("/home/sfischme/Documents/acerta/tstat/site/Rserver")
source("server.R")
setwd(q)

library(microbenchmark)

library(bit64)

################################################################################
################################################################################
################################################################################

library(ggmap)


files <- list.files("augusto-bike-rides/",pattern="^ride*")
#files <- "ride032.csv" ## problem, this doesn't work

# uphill/downhill 
slope <- dat$slope
total <- length(slope)
uphill <- length(which(slope > 0)) / total * 100
downhill <- length(which(slope < 0)) / total * 100
level <- length(which(slope == 0)) / total * 100

slope.max <- max(abs(slope), na.rm=T)
slope.min <- min(abs(slope), na.rm=T)

up.max <- max(slope, na.rm=T)
up.min <- min(slope[slope > 0], na.rm=T)

down.max <- min(slope, na.rm=T)
down.min <- max(slope[slope < 0], na.rm=T)

foreach (f=files) %do% {
    prefix <- gsub("\\.csv$","",f)
    message(f)
    dat <- fread(paste0("augusto-bike-rides/",f))[,c("time", "latitude", "longitude", "altitude", "speed", "pace", "course", "slope", "distance", "distance_interval"),with=F] %>%
        prepareGPSData(3) %>%
        detectDrivingDirection(3) %>%
        detectDrivingScenarios() %>%
        detectTurns(7.5,2)

    #dat <- dat[speed<70]
    #max(dat$speed)

    xbound <- max(abs(min(dat$latitude.delta, na.rm=T)), max(dat$latitude.delta, na.rm=T))
    ybound <- max(abs(min(dat$longitude.delta, na.rm=T)),max(dat$longitude.delta, na.rm=T))

    bbox <- make_bbox(dat$longitude,dat$latitude)
    map_loc <- get_map(bbox, source="osm")## maptype = 'satellite')
    ## map_loc <- get_map(c(long=mean(bbox[1],bbox[3])+0.003,lat=mean(bbox[2],bbox[4])+0.003),zoom=16, source="google")## ma
    ## map_loc <- get_map(c(long=mean(bbox[1],bbox[3]),lat=mean(bbox[2],bbox[4])),zoom=8, source="google")## ma

    map <- ggmap(map_loc, extent = 'device')

    map + geom_point(data=dat,aes(x=longitude,y=latitude),color="royalblue",size=2) +
        ggtitle("Map")
    ggsave(last_plot(),file=paste0(prefix,"-drive-map.pdf"))

    ## turns analysis
    map + geom_path(data=dat,aes(x=longitude,y=latitude),color="black",size=1) +
        geom_point(data=dat[turn!=0],aes(x=longitude,y=latitude, color=factor(turn)), size=3) +
        scale_color_brewer("Turns",labels=c("-1"="Right","1"="Left"),palette="Set1") +
        ggtitle("Map")
    ggsave(last_plot(),file=paste0(prefix,"-drive-map-with-turns.pdf"))


    ggplot(dat[turn!=0]) + geom_bar(aes(x=factor(turn))) +
        scale_x_discrete("Turns",label=list("-1"="Right","1"="Left")) + ylab("Count") + ggtitle("Turns")
    ggsave(last_plot(),file=paste0(prefix,"-drive-bar-turns.pdf"))

    ## directions exposure

    map + geom_point(data=dat,aes(x=longitude,y=latitude,color=phi.ccat),size=2) +
        scale_colour_brewer(name="Driving\nDirection",palette="Set1") +
        theme(legend.position=c(1,0),legend.justification=c(1,0)) +
        ggtitle("Map Directions Exposure")
    ggsave(last_plot(),file=paste0(prefix,"-drive-map-directions-exposure.pdf"))

    ggplot(dat) + geom_bar(aes(x=phi.ccat,weight=distance_interval),binwith=5) +
        xlab("Direction") + ylab("Distance [m]") +
        ggtitle("Exposure")
    ggsave(last_plot(),file=paste0(prefix,"-drive-bar-exposure.pdf"))


    ggplot(dat,aes(x=course,weight=distance_interval)) +
        ggtitle("Exposure Vectorgram") +
        xlab("") + ylab("") +
        geom_bar(binwidth=360/16) +
        scale_x_continuous() +
        coord_polar() +
        theme(legend.position="none")
    ggsave(last_plot(),file=paste0(prefix,"-drive-vectorgram-exposure.pdf"))

    ggplot(dat,aes(x=0, y=0, color=phi.ccat)) +
        ggtitle("Driving Vectorgram") +
        xlab("") + ylab("") +
        scale_colour_brewer(name="Driving\nDirection",palette="Set1") +
        coord_cartesian(xlim= c(-xbound,xbound), ylim=c(-ybound,ybound)) +
        theme(legend.position=c(1,0),legend.justification=c(1,0)) +
        geom_segment(aes(xend=latitude.delta,yend=longitude.delta), arrow = arrow(length=unit(0.1,"cm") ))
    ggsave(last_plot(),file=paste0(prefix,"-drive-vectorgram-directions.pdf"))


    ## speed

    map + geom_point(data=dat,aes(x=longitude,y=latitude,color=speed),size=2) +
        scale_colour_gradient(name="Speed (km/h)",low="blue",high="red") +
        theme(legend.position=c(1,0),legend.justification=c(1,0)) +
        ggtitle("Map Speed")
    ggsave(last_plot(),file=paste0(prefix,"-drive-map-velocity.pdf"))

    ggplot(dat) + geom_bar(aes(x=speed,weight=distance_interval),binwith=5) +
        xlab("Speed [km/h]") + ylab("Distance [m]") +
        ggtitle("Speed Profile")
    ggsave(last_plot(),file=paste0(prefix,"-drive-bar-speed.pdf"))

    ## acceleration

    ggplot(dat,aes(x=t, y=0)) +
        ggtitle("Acceleration Vectorgram") +
        xlab("Time [s]") + ylab("Acceleration") +
        geom_segment(aes(xend=t,yend=acceleration), arrow = arrow(length=unit(0.1,"cm") ))
    ggsave(last_plot(),file=paste0(prefix,"-drive-vectorgram-acceleration.pdf"))

    ggplot(dat) + geom_bar(aes(x=acceleration),binwidth=1) +
        xlab("Acceleration [km/h^2]") + ylab("Count") +
        ggtitle("Acceleration Profile")
    ggsave(last_plot(),file=paste0(prefix,"-drive-bar-acceleration.pdf"))

    map + geom_point(data=dat,aes(x=longitude,y=latitude,color=acceleration),size=2) +
        scale_colour_gradient(name="Velocity",low="blue",high="red") +
        theme(legend.position="none") +
        ggtitle("Map Acceleration")
    ggsave(last_plot(),file=paste0(prefix,"-drive-map-acceleration.pdf"))


### Altitude

    ggplot(dat) + geom_point(aes(x=t,y=altitude),color="black",size=1.5) +
        ggtitle("Profile") + xlab("Time") + ylab("Level [m]") +
        theme(legend.position="none")
    ggsave(last_plot(),file=paste0(prefix,"-drive-profile-altitude.pdf"))


    map + geom_point(data=dat,aes(x=longitude,y=latitude,color=altitude),size=2) +
        scale_colour_gradient(name="Altitude",low="blue",high="red") +
        theme(legend.position=c(1,0),legend.justification=c(1,0)) +
        ggtitle("Map Altitude Profile")
    ggsave(last_plot(),file=paste0(prefix,"-drive-map-altitude.pdf"))

    ggplot(dat,aes(x=t, y=0)) +
        ggtitle("Altitude Vectorgram") +
        xlab("Time [s]") + ylab("Altitude change [m]") +
        geom_segment(aes(xend=t,yend=altitude.delta/t.delta), arrow = arrow(length=unit(0.1,"cm") ))
    ggsave(last_plot(),file=paste0(prefix,"-drive-vectorgram-altitude.pdf"))


    ## lighting exposures

    map + geom_point(data=dat,aes(x=longitude,y=latitude,color=insun),size=2) +
        scale_colour_brewer("Driving",labels=c("FALSE"="Ignored", "TRUE"="Into sun"),palette="Set1") +
        theme(legend.position=c(1,0),legend.justification=c(1,0)) +
        ggtitle("Map Scenario: Driving into the Sun")
    ggsave(last_plot(),file=paste0(prefix,"-drive-map-into-sun.pdf"))

    ggplot(dat) + geom_bar(aes(x=factor(dusk),weight=distance_interval/1000),binwith=5) +
        scale_x_discrete("",labels=c("FALSE"="No dusk", "TRUE"="Dusk")) +
        ylab("Distance [km]") +
        ggtitle("Explosure: Dusk")
    ggsave(last_plot(),file=paste0(prefix,"-drive-bar-dusk.pdf"))

    ggplot(dat) + geom_bar(aes(x=factor(dawn),weight=distance_interval/1000),binwith=5) +
        scale_x_discrete("",labels=c("FALSE"="No dawn", "TRUE"="Dawn")) +
        ylab("Distance [km]") +
        ggtitle("Explosure: Dawn")
    ggsave(last_plot(),file=paste0(prefix,"-drive-bar-dawn.pdf"))

    ggplot(dat) + geom_bar(aes(x=day,weight=distance_interval/1000),binwith=5) +
        scale_x_discrete("",labels=c("FALSE"="Night time", "TRUE"="Day time")) +
        xlab("Direction") + ylab("Distance [km]") +
        ggtitle("Explosure: Day/Night")
    ggsave(last_plot(),file=paste0(prefix,"-drive-bar-day-night.pdf"))

    ggplot(dat) + geom_bar(aes(x=insun,weight=distance_interval/1000),binwith=5) +
        scale_x_discrete("",labels=c("FALSE"="Sun irrelevant", "TRUE"="Into sun")) +
        xlab("Direction") + ylab("Distance [km]") +
        ggtitle("Explosure: Dusk")
    ggsave(last_plot(),file=paste0(prefix,"-drive-bar-in-sun.pdf"))

    NULL
}




#### Summary statistics


files

dat <- lapply(files,function(fin) fread(paste0("augusto-bike-rides/",fin))[,c("time", "latitude", "longitude", "altitude", "speed", "pace", "course", "slope", "distance", "distance_interval"),with=F] %>%
                           prepareGPSData(3) %>%
                           detectDrivingDirection(3) %>%
                           detectDrivingScenarios() %>%
                           detectTurns(7.5,2) )

dat <- rbind.fill(dat) %>% data.table()




















prepareGPSData <- function(dat,SMOOTH_SECONDS) {
    dat[,cnt:=1:nrow(dat)]
    angle2 <- function(x1,y1,x2,y2){
        ## right turns are be positive values
        ang <- (atan2(y2,x2) - atan2(y1,x1))/pi*180
        ang[ abs(ang) > 280 ] <- NA    ## limit of atan; after 270 degree, you're still moving forward
        return(ang)
    }

    f <- rep(1/SMOOTH_SECONDS,SMOOTH_SECONDS)

    dat[,latitude := stats::filter(latitude,f) %>% as.numeric()]
    dat[,longitude := stats::filter(longitude,f) %>% as.numeric()]
    dat[,altitude := stats::filter(altitude,f) %>% as.numeric()]

    dat[,latitude.delta := c(diff(latitude),NA)]
    dat[,longitude.delta := c(diff(longitude),NA)]
    dat[,altitude.delta := c(diff(altitude),NA)]

    dat[, velocity:=sqrt(latitude*latitude+longitude*longitude)]
    dat[, velocity.delta:=c(diff(velocity),NA)]

    dat <- dat[complete.cases(dat)]
    dat[, angle:=angle2(latitude.delta, longitude.delta, shift(latitude.delta), shift(longitude.delta))]

    dat[,t:=data.frame(strptime(time,format="%Y-%m-%d %H:%M:%S")-21600)] ## TODO: no clue why a dataframe is needed ## TODO: smarter time conversion
    dat[,t.delta:=c(0,diff(t))]
    dat[,acceleration:=c(0,diff(speed))/t.delta]

    return(dat)
}

detectDrivingScenarios <- function(dat) {
    ## find interesting scenarios
    dat[,dusk:= (findInterval(as.numeric(format(t, "%H")) +  as.numeric(format(t, "%M"))/60, c(17.5,20)) == 1)]
    dat[,dawn:= findInterval(as.numeric(format(t, "%H")) +  as.numeric(format(t, "%M"))/60, c(6.5,8)) == 1]
    dat[,sunrise:= findInterval(as.numeric(format(t, "%H")) +  as.numeric(format(t, "%M"))/60, c(7.5,10)) == 1]
    dat[,sunset:= findInterval(as.numeric(format(t, "%H")) +  as.numeric(format(t, "%M"))/60, c(15.5,18)) == 1]
    dat[,insun:= (sunrise & phi.ccat=="E") | (sunset & phi.ccat=="W")]
    dat[,day:= findInterval(as.numeric(format(t, "%H")) +  as.numeric(format(t, "%M"))/60, c(6.5,18.5)) == 1]
    return(dat)
}

detectDrivingDirection <- function(dat, THRESH_MIN_DIRECTION_DRIVE_SAMPLES) {
    ## compute the absolute direction angle of each driving vector
    dat[,phi:=(atan2(longitude.delta,latitude.delta)*180/pi)]

    ## categorize into 8 driving directions
    DRIVING_DIRECTIONS <- 8
    dat[,phi.cat:=(floor(((dat$phi+45/2) / (360/DRIVING_DIRECTIONS))))]  ## shift by 45 degree to have proper N NE E SE S SW W NW categories
    #dat[, phi.cat:= ((dat$course) / (360/DRIVING_DIRECTIONS)) ]
    ##dat[phi.cat==-4,phi.cat:=4]
    ## clean sparse trains by iteratively deleting short trains, so transient faults do not cut large trains

    mergeSparseCategories <- function(data, THRESH_SPARSE_TRAIN) {
        repeat {
            data[, rle1:=cumsum(c(0,diff(phi.cat))!=0) ]
            ## plot(data$rle1)
            data[, rle2:=.N,by=rle1]
            ## plot(data$rle2)
            if (min (data$rle2) >= THRESH_SPARSE_TRAIN) break;
            data <- data[rle2 != min(data$rle2)]
        }
        return(data[,c("cnt","phi.cat"),with=F])
    }

    dat.tmp <- mergeSparseCategories(dat, THRESH_MIN_DIRECTION_DRIVE_SAMPLES)
    setnames(dat.tmp,"phi.cat","phi.ccat")

    dat <- merge(x=dat, y=dat.tmp, by="cnt", all.x=TRUE)

    dat$phi.ccat <- factor(dat$phi.ccat)
#    levels(dat$phi.ccat) <- list("SW"=-3,"S"=-2,"SE"=-1,"E"=0,"NE"=1,"N"=2,"NW"=3,"W"=4)
    levels(dat$phi.ccat) <- list("SW"=-3,"W" =-2,"NW"=-1,"N"=0,"NE"=1,"E"=2,"SE"=3,"S" =4)   ## Augusto's GPS

    dat <- dat[!is.na(phi.ccat)]
    dat[,cnt:=1:.N]

    return(dat)
}

detectTurns <- function(dat, THRESH_CURVE_ANGLE, THRES_MIN_CURVE_SAMPLES) {
    ## clean up angles
    dat[is.na(angle),angle:=0]
    dat[,turn:=ifelse(angle>THRESH_CURVE_ANGLE,1,0)]
    dat[angle < -THRESH_CURVE_ANGLE, turn:=-1]

    mergeSparseCategories <- function(data, THRES_SPARSE_TRAIN) {
        repeat {
            data[, rle1:=cumsum(c(0,diff(turn))!=0) ]
            ## plot(data$rle1)
            data[, rle2:=.N,by=rle1]
            ## plot(data$rle2)
            if (min (data$rle2) >= THRES_SPARSE_TRAIN) break;
            data <- data[rle2 != min(data$rle2)]
        }
        return(data[,c("cnt","turn"),with=F])
    }

    dat.tmp <- mergeSparseCategories(dat, THRES_MIN_CURVE_SAMPLES)
    dat[,turn:=NULL]
    dat <- merge(x=dat, y=dat.tmp, by="cnt", all.x=TRUE)

    return (dat)
}




################################################################################
################################################################################
################################################################################






for(i in 1:length(files)) {
    dat <- copy(dat.cp[dat.cp$file==files[i]])

    dat <- data.table(latitude=substr(dat$gps_latitude, 1, nchar(dat$gps_latitude)-1) %>% as.numeric(),
                      longitude=substr(dat$gps_longitude, 1, nchar(dat$gps_longitude)-1) %>% as.numeric(),
                      altitude=dat$gps_altitude)

## clean the data

    dat <- dat[complete.cases(dat)]
    dat <- dat[dat$latitude > 10]
    dat <- dat[dat$longitude > 10]

    p1 <- ggplot(dat,aes(x=longitude, y=latitude, color = altitude)) +  geom_path() + geom_point() + ggtitle(files[i])
    try(ggsave(p1, file=paste0("plot-file-",i,".pdf")))
}

dat

for(i in seq(500,nrow(dat),60) ) {
    p1 <- ggplot(dat[(i-500):i]  ,aes(x=-longitude, y=latitude, color = altitude)) +  geom_path() + geom_point() + ggtitle(files[i])
    print(p1)
    readline()
}
